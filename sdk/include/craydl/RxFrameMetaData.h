#ifndef RX_FRAME_META_DATA_H
#define RX_FRAME_META_DATA_H

#include <boost/date_time.hpp>
#include <boost/format.hpp>

#include "RxTransformation.h"
#include "RxUtils.h"

namespace craydl {

using std::endl;

typedef boost::posix_time::ptime RxTimestamp_t;
typedef boost::posix_time::time_duration RxTimeDuration_t;

enum RxRotationAxis_t {TwoTheta, Omega, Chi, Kappa, Phi, Delta, Gamma, Distance};

// Advance declaration
class RxFrame;

typedef uint32_t FrameChecksum_t;

class ExperimentMetaData
{
   //friend class RxFrame;

   public:
      ExperimentMetaData() {}
      ~ExperimentMetaData() {}

      // Experimental data getters
      std::string Comment() { return file_comment_; }
      std::string DatasetComment() { return dataset_comment_; }

      std::pair<double,double> BeamPosition() { return beam_position_; }
      //nanoMeters
      double SourceXRayWavelength() const { return source_xray_wavelength_; }
      //eV
      double SourceXRayEnergy() const { return EV(source_xray_wavelength_ * 1.0E1); }
      double SampleToDetectorDistance() const { return sample_to_detector_distance_; }
      RxRotationAxis_t SampleRotationAxis() const { return sample_rotation_axis_; }
      double SampleRotationRange() const { return sample_rotation_range_; }
      double SampleOmega() const { return sample_omega_; }
      double SampleChi() const { return sample_chi_; }
      double SampleKappa() const { return sample_kappa_; }
      double SamplePhi() const { return sample_phi_; }
      double SampleDelta() const { return sample_delta_; }
      double SampleGamma() const { return sample_gamma_; }
      double DetectorTwoTheta() const { return detector_two_theta_; }
      double DetectorRotX() const { return detector_rot_x_; }
      double DetectorRotY() const { return detector_rot_y_; }
      double DetectorRotZ() const { return detector_rot_z_; }

      double ExposureTime() { return exposure_time_; }


      // Experimental data setters
      void setComment(const std::string &comment) { file_comment_ = comment; }
      void setDatasetComment(const std::string &comment) { dataset_comment_ = comment; }
      void setBeamPositionX(double mm) {beam_position_.first = mm;}
      void setBeamPositionY(double mm) {beam_position_.second = mm;}
      void setBeamPosition(std::pair<double,double> mm) { beam_position_ = mm; }
      void setSourceXRayWavelength(double nm) { source_xray_wavelength_ = nm; }
      void setSourceXRayEnergy(double eV) { source_xray_wavelength_ = ANGSTROM(eV)*1.0E-1; }
      void setSampleToDetectorDistance(double mm) { sample_to_detector_distance_ = mm; }
      void setSampleRotationAxis(RxRotationAxis_t index) { sample_rotation_axis_ = index; }
      void setSampleRotationRange(double degrees) { sample_rotation_range_ = degrees; }
      void setSampleOmega(double degrees) { sample_omega_ = degrees; }
      void setSampleChi(double degrees) { sample_chi_ = degrees; }
      void setSampleKappa(double degrees) { sample_kappa_ = degrees; }
      void setSamplePhi(double degrees) { sample_phi_ = degrees; }
      void setSampleDelta(double degrees) { sample_delta_ = degrees; }
      void setSampleGamma(double degrees) { sample_gamma_ = degrees; }
      void setDetectorTwoTheta(double degrees) { detector_two_theta_ = degrees; }
      void setDetectorRotX(double degrees) { detector_rot_x_ = degrees; }
      void setDetectorRotY(double degrees) { detector_rot_y_ = degrees; }
      void setDetectorRotZ(double degrees) { detector_rot_z_ = degrees; }

      void AdvanceRotationByN(int N) {
	 switch(SampleRotationAxis()) {
	    case TwoTheta:
	       setDetectorTwoTheta(DetectorTwoTheta()+N*SampleRotationRange());
	       break;
	    case Omega:
	       setSampleOmega(SampleOmega()+N*SampleRotationRange());
	       break;
	    case Chi:
	       setSampleChi(SampleChi()+N*SampleRotationRange());
	       break;
	    case Kappa:
	       setSampleKappa(SampleKappa()+N*SampleRotationRange());
	       break;
	    case Phi:
	       setSamplePhi(SamplePhi()+N*SampleRotationRange());
	       break;
	    case Delta:
	       setSampleDelta(SampleDelta()+N*SampleRotationRange());
	       break;
	    case Gamma:
	       setSampleGamma(SampleGamma()+N*SampleRotationRange());
	       break;
	    case Distance:
	       setSampleToDetectorDistance(SampleToDetectorDistance()+N*SampleRotationRange());
	       break;
	    default: 
	       break;
	 }
      }

      void setExposureTime(double secs) { exposure_time_ = secs; }
      //void setIntegrationTime(double secs) { integration_time_ = secs; }
      //void setReadoutTime(double secs) { readout_time_ = secs; }

   protected:

      // General
      std::string file_comment_;
      std::string dataset_comment_;


      // Experimental environment
      std::pair<double,double> beam_position_;
      double source_xray_wavelength_;
      double sample_to_detector_distance_;
      RxRotationAxis_t sample_rotation_axis_;
      double sample_rotation_range_;
      double sample_omega_;
      double sample_chi_;
      double sample_kappa_;
      double sample_phi_;
      double sample_delta_;
      double sample_gamma_;
      double detector_two_theta_;
      double detector_rot_x_;
      double detector_rot_y_;
      double detector_rot_z_;

      double exposure_time_;

};

//class FrameMetaData : public RxMetaData
class FrameMetaData
{
   friend class RxFrame;

   public:
      FrameMetaData() :
	 saved_filename_(""),
	 saved_(false),
	 valid_data_(false), 
	 valid_raw_data_(false), 
	 internal_frame_ID(0),
	 correction_applied_(false),
	 staturated_level_(0),
	 staturated_flag_(0),
	 nreads_(1),
	 prescan_trimmed(false),
	 postscan_trimmed(false),
	 prescan_fast(0),
	 prescan_slow(0),
	 postscan_fast(0),
	 postscan_slow(0),
	 bias_subtracted(false),
	 dark_subtracted(false),
	 flatfield_applied(false),
	 geometric_correction_applied(false),
	 pedestal(0),
	 software_binning_fast(1),
	 software_binning_slow(1),
	 hardware_binning_fast(1),
	 hardware_binning_slow(1),
	 n_sections_fast_(1),
	 n_sections_slow_(1),
	 mean(0.0),
	 stddev(0.0),
	 min(0),
	 max(0),
	 n_zeros(0),
	 n_saturated(0),
	 stats_valid(false)
	 {}
      ~FrameMetaData() {}

      FrameChecksum_t frameIntegrityChecksum() const {return frame_checksum_;}
      bool dataIsValid() const {return valid_data_;}
      bool rawDataIsValid() const {return valid_raw_data_;}
      bool correctionIsApplied() const {return correction_applied_;}

      void setFrameIntegrityChecksum(FrameChecksum_t checksum) { frame_checksum_ = checksum;} 
      void setDataIsValid(bool valid) {valid_data_ = valid;}
      void setRawDataIsValid(bool valid) {valid_raw_data_ = valid;}
      void setCorrectionIsApplied(bool valid) {correction_applied_ = valid;}

      static RxTimestamp_t stampTimestamp() { return boost::posix_time::microsec_clock::local_time(); }

      RxTimeDuration_t ExposureElapsedTime() const;
      RxTimeDuration_t ReadoutElapsedTime() const;
      RxTimeDuration_t AcquisitionElapsedTime() const;
      RxTimeDuration_t CorrectionElapsedTime() const;
      RxTimeDuration_t WriteElapsedTime() const;
      RxTimestamp_t AcquisitionEndTimestamp() const;
      RxTimestamp_t CorrectionEndTimestamp() const;
      RxTimestamp_t ExposureEndTimestamp() const;
      RxTimestamp_t ReadoutEndTimestamp() const;
      RxTimestamp_t WriteEndTimestamp() const;
      RxTimestamp_t AcquisitionStartTimestamp() const;
      RxTimestamp_t CorrectionStartTimestamp() const;
      RxTimestamp_t ExposureStartTimestamp() const;
      RxTimestamp_t ReadoutStartTimestamp() const;
      RxTimestamp_t WriteStartTimestamp() const;
      RxTimestamp_t HardwareTimestamp() const;

      void setTimestamp(RxTimestamp_t& timestamp, const RxTimestamp_t& time = boost::posix_time::not_a_date_time);

      void setExposureEndTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setReadoutEndTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setAcquisitionEndTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setCorrectionEndTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setWriteEndTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);

      void setExposureStartTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setReadoutStartTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setAcquisitionStartTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setCorrectionStartTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);
      void setWriteStartTimestamp(RxTimestamp_t timestamp = boost::posix_time::not_a_date_time);

      void setHardwareTimestamp(RxTimestamp_t timestamp);

      int getNReads() const
      {
	 return nreads_;
      }

      void setNReads(int nreads)
      {
	 nreads_ = nreads;
      }

      int NSectionsFast() const { return n_sections_fast_; }
      int NSectionsSlow() const { return n_sections_slow_; }

      void setNSectionsFast(int sections) { n_sections_fast_ = sections; }
      void setNSectionsSlow(int sections) { n_sections_slow_ = sections; }

      // Overall Binning 

      int binningFast() const { return softwareBinningFast() * hardwareBinningFast(); }

      int binningSlow() const { return softwareBinningSlow() * hardwareBinningSlow(); }

      // Software Binning 
      int softwareBinningFast() const { return software_binning_fast; }

      int softwareBinningSlow() const { return software_binning_slow; }

      void setSoftwareBinningFast(int binning) { software_binning_fast = binning; }

      void setSoftwareBinningSlow(int binning) { software_binning_slow = binning; }

      // Hardware Binning 
      int hardwareBinningFast() const { return hardware_binning_fast; }

      int hardwareBinningSlow() const { return hardware_binning_slow; }

      void setHardwareBinningFast(int binning) { hardware_binning_fast = binning; }

      void setHardwareBinningSlow(int binning) { hardware_binning_slow = binning; }

      std::pair<double,double> PixelSize() { return pixelsize_; }

      void setPixelSize(std::pair<double,double> mm) { pixelsize_ = mm; }

      void swapFastAndSlow()
      {
	 std::swap(prescan_fast, prescan_slow);
	 std::swap(postscan_fast, postscan_slow);
	 std::swap(software_binning_fast, software_binning_slow);
	 std::swap(hardware_binning_fast, hardware_binning_slow);
	 std::swap(n_sections_fast_, n_sections_slow_);
	 return;
      }


      ExperimentMetaData experiment;

   private:
      std::string saved_filename_;
      bool saved_;
      RxTimestamp_t AcquisitionStartTimestamp_;
      RxTimestamp_t AcquisitionEndTimestamp_;
      RxTimestamp_t ExposureStartTimestamp_;
      RxTimestamp_t ExposureEndTimestamp_;
      RxTimestamp_t ReadoutStartTimestamp_;
      RxTimestamp_t ReadoutEndTimestamp_;
      RxTimestamp_t CorrectionStartTimestamp_;
      RxTimestamp_t CorrectionEndTimestamp_;
      RxTimestamp_t WriteStartTimestamp_;
      RxTimestamp_t WriteEndTimestamp_;
      RxTimestamp_t HardwareTimestamp_;
      FrameChecksum_t frame_checksum_;
      bool valid_data_;
      bool valid_raw_data_;
      int internal_frame_ID;
      bool correction_applied_;

      // Geometry
      RxOrientation orientation_;
      std::pair<double,double> pixelsize_;

      std::string comment;
      std::map<std::string, double> detector_translations;
      std::map<std::string, double> detector_rotations;
      std::map<std::string, double> axis_positions;
      std::map<std::string, double> source_parameters;
      std::map<std::string, double> optics_parameters;

      int staturated_level_;
      int staturated_flag_;
      int nreads_;
      bool prescan_trimmed;
      bool postscan_trimmed;
      int prescan_fast;
      int prescan_slow;
      int postscan_fast;
      int postscan_slow;
      bool bias_subtracted;
      bool dark_subtracted;
      bool flatfield_applied;
      bool geometric_correction_applied;
      int pedestal;
      int software_binning_fast;
      int software_binning_slow;
      int hardware_binning_fast;
      int hardware_binning_slow;

      int n_sections_fast_;
      int n_sections_slow_;

      // Stats
      double mean;
      double stddev;
      int min;
      int max;
      int n_zeros;
      int n_saturated;
      bool stats_valid;


};

}

#endif //RX_FRAME_META_DATA_H
