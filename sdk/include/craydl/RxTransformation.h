#ifndef RX_TRANSFORMATION_H
#define RX_TRANSFORMATION_H

#include <ostream>

namespace craydl {

enum RxTransformationCode_t {R0, R90, R180, R270, M0, M45, M90, M135};

static std::string TransformName[] = {
   "R0", "R90", "R180", "R270", "M0", "M45", "M90", "M135"
};

static bool AxisSwap[] = {
   false, true, false, true, false, true, false, true
};

static RxTransformationCode_t TransformInverse[] = {
   R0, R270, R180, R90, M0, M45, M90, M135
};

// These transforms can be thought of as names of matrices
// Operation rules are the same for as for matrices
// eg,   AB != BA,   A(BC) = (AB)C
// Note that R0 is the identity matrix
// To use this array of arrays to compute a product
// C = AB
// C = TransformProduct[A][B]
// specific examples:
// M135 = TransformProduct[M0][R90]
// M45  = TransformProduct[R90][M0]

static RxTransformationCode_t TransformProduct[][8] = {
   {   R0, R90,R180,R270,  M0, M45, M90,M135},
   {  R90,R180,R270,  R0, M45, M90,M135,  M0},
   { R180,R270,  R0, R90, M90,M135,  M0, M45},
   { R270,  R0, R90,R180,M135,  M0, M45, M90},
   {   M0,M135, M90, M45,  R0,R270,R180, R90},
   {  M45,  M0,M135, M90, R90,  R0,R270,R180},
   {  M90, M45,  M0,M135,R180, R90,  R0,R270},
   { M135, M90, M45,  M0,R270,R180, R90,  R0}
};

inline std::string TransformationCodeToString(RxTransformationCode_t code)
{
   return TransformName[code];
}

inline RxTransformationCode_t StringToTransformationCode(const std::string& string)
{
   std::vector<std::string> name_vector(TransformName, TransformName + sizeof(TransformName)/sizeof(TransformName[0]));

   RxTransformationCode_t  the_code = R0;
   for (std::vector<std::string>::const_iterator ni = name_vector.begin(); ni != name_vector.end(); ++ni) {
      if (string == *ni) {
	 the_code = (RxTransformationCode_t)(ni - name_vector.begin());
	 break;
      }
   }

   //std::cerr << "translate " << string << " to " << the_code << " (" << TransformationCodeToString(the_code) << ")" << std::endl;
   return the_code;

}

class RxTransformation {
   public:
      RxTransformation(RxTransformationCode_t transformation_code = R0) {transformation_code_ = transformation_code;}
      RxTransformationCode_t transformation()
      {
	 return transformation_code_;
      }
      RxTransformationCode_t resulting_orientation()
      {
	 return transformation_code_;
      }
      void invert()
      {
	 transformation_code_ = inverse();
	 return;
      }
      void transform(RxTransformationCode_t transformation_code)
      {
	 transformation_code_ = transformation_product(transformation_code, transformation_code_);
	 return;
      }
      RxTransformationCode_t inverse()
      {
	 return TransformInverse[transformation_code_];
      }
      bool axis_swap()
      {
	 return AxisSwap[transformation_code_];
      }
      static RxTransformationCode_t inverse(RxTransformationCode_t transformation_code)
      {
	 return TransformInverse[transformation_code];
      }
      static RxTransformationCode_t transformation_product(const std::vector<RxTransformationCode_t>& transformation_list)
      {

	 std::vector<RxTransformationCode_t>::const_iterator txli = transformation_list.end();

	 if (transformation_list.empty()) return R0;

	 // The return the last element
	 if (transformation_list.size() < 2) return *(--txli);

	 // The return the product of last element * next to last element
	 if (transformation_list.size() == 2) {
	    std::vector<RxTransformationCode_t>::const_iterator txli2 = --txli;
	    --txli;
	    //return TransformProduct[*txli2][*txli];
	    return transformation_product(*txli2, *txli);
	 }

	 // replace the last two elements with a singl element equal to the product of last element * next to last element
	 std::vector<RxTransformationCode_t> full_list = transformation_list;
	 std::vector<RxTransformationCode_t> last_pair;

	 while (full_list.size() > 1) {
	    std::vector<RxTransformationCode_t>::iterator fli = full_list.end();
	    last_pair.clear();
	    // last element
	    --fli;
	    last_pair.push_back(*fli);
	    if (fli != full_list.begin()) {
	       // next to last element
	       --fli;
	       last_pair.insert(last_pair.begin(), *fli);
	       // Remove last on full list
	       full_list.pop_back();
	    }
	    // Remove last on full list (next to last, if last was already removed)
	    full_list.pop_back();
	    // calcualte product of last pair and push this back onto end of list
	    full_list.push_back(transformation_product(last_pair));
	 }
	 // When finished, the list has one element witht he product stored in it
	 return *full_list.begin();
      }

      static RxTransformationCode_t transformation_product(RxTransformationCode_t transformation2, RxTransformationCode_t transformation1 )
      {
	 RxTransformationCode_t result_code = TransformProduct[transformation2][transformation1];

	 //std::cerr << "RxTransformation::transformation_product(): " << TransformationCodeToString(result_code) << " = " << TransformationCodeToString(transformation2) << "x" << TransformationCodeToString(transformation1)  << std::endl;

	 return result_code;
      }
   private:
      RxTransformationCode_t transformation_code_;
};

class RxOrientation
{
   public:
      RxOrientation(RxTransformation transformation = R0) {orientation_code_ = transformation.resulting_orientation();}
      RxTransformationCode_t orientation()
      {
	 return orientation_code_;
      }

      RxTransformationCode_t transformation_from()
      {
	 return RxTransformation::inverse(orientation_code_);
      }

      RxTransformationCode_t transformation_to()
      {
	 return orientation_code_;
      }

   private:
      RxTransformationCode_t orientation_code_;
};

}

#endif // RX_TRANSFORMATION_H
