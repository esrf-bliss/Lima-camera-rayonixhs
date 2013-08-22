#ifndef __CONFIG_FILE_H__
#define __CONFIG_FILE_H__

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ostream>

#include "Chameleon.h"
#include <boost/filesystem.hpp>

namespace craydl {

class ConfigFile
{

   public:
      ConfigFile(std::string const& configFile);
      ConfigFile(std::string const& searchPath, std::string const& configFile);

      bool Present(std::string const& section_list, std::string const& entry) const;

      bool SectionPresent(std::string const& section) const;

      Chameleon const& Value(std::string const& section_list, std::string const& entry) const;

      template <class T>
      Chameleon const& Value(std::string const& section_list, std::string const& entry, const T& value);

      // Canonical must wait for boost v3
      //std::string Filename() { try { filename_ = boost::filesystem::canonical(filename_).string(); } catch (...) { filename_ = boost::filesystem::absolute(filename_).string(); } return filename_; }
      std::string Filename() { try { filename_ = boost::filesystem::absolute(filename_).string(); } catch (...) { filename_ = boost::filesystem::absolute(filename_).string(); } return filename_; }

   private:
      bool OpenFile(std::string const& configFile);

   private:
      std::map<std::string,Chameleon> content_;
      std::string filename_;
};

inline std::string trim(std::string const& source, char const* delims = " \t\r\n")
{
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

inline void get_sections(const std::string& str, std::vector<std::string>& tokens)
{
   std::string delimiters(",");

   // Skip delimiters at beginning.
   std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
   // Find first "non-delimiter".
   std::string::size_type pos = str.find_first_of(delimiters, lastPos);

   while (std::string::npos != pos || std::string::npos != lastPos) {
      // Found a token, add it to the vector.
      tokens.push_back(str.substr(lastPos, pos - lastPos));
      // Skip delimiters.  Note the "not_of"
      lastPos = str.find_first_not_of(delimiters, pos);
      // Find next "non-delimiter"
      pos = str.find_first_of(delimiters, lastPos);
   }

   return;
}

inline ConfigFile::ConfigFile(std::string const& searchPath, std::string const& configFile) :
   filename_("")
{
   std::string filename(configFile);;
   std::vector<std::string> tried;

   if (!searchPath.empty()) {
      if (configFile.compare(0,1,"/") == 0) {
	 tried.push_back(filename);
      }
      else {

	 std::vector<std::string> paths;
	 std::string delimiters(",:");

	 filename.clear();

	 // Skip delimiters at beginning.
	 std::string::size_type lastPos = searchPath.find_first_not_of(delimiters, 0);

	 // Find first "non-delimiter".
	 std::string::size_type pos = searchPath.find_first_of(delimiters, lastPos);

	 while (std::string::npos != pos || std::string::npos != lastPos) {

	    paths.push_back(searchPath.substr(lastPos, pos - lastPos));

	    // Skip delimiters.  Note the "not_of"
	    lastPos = searchPath.find_first_not_of(delimiters, pos);
	    // Find next "non-delimiter"
	    pos = searchPath.find_first_of(delimiters, lastPos);

	 }

	 for ( std::vector<std::string>::const_iterator path = paths.begin(); path != paths.end(); ++path) {
	    filename = *path + std::string("/") + configFile;
	    boost::filesystem::path p = boost::filesystem::absolute(filename);
	    filename = p.string();
	    //std::cout << "Testing: " << filename << std::endl;
	    std::ifstream file(filename.c_str());
	    if (file) {
	       // It exists, stop searching
	       break;
	    }
	    tried.push_back(filename);
	 }
      }
   }
   if (!OpenFile(filename)) {
      std::cerr << "WARNING - Failed to find configuration file.  Tried:"<< std::endl;
      for ( std::vector<std::string>::const_iterator name = tried.begin(); name != tried.end(); ++name) {
	 std::cerr << "         " << *name << std::endl;
      }
   }
   else {
      //std::cerr << "Reading configuration data from: " << filename << std::endl;
   }
}

inline ConfigFile::ConfigFile(std::string const& configFile)
{
   OpenFile(configFile);
}

inline bool ConfigFile::OpenFile(std::string const& configFile)
{
  std::ifstream file(configFile.c_str());

  if (!file) return false;

  filename_ = configFile;

  std::string line;
  std::string name;
  std::string value;
  std::string inSection;
  int posEqual;
  while (std::getline(file,line)) {

    if (! line.length()) continue;

    if (line[0] == '#') continue;
    if (line[0] == ';') continue;
    
    //Remove anything after comment character on line
    size_t comment_pos = line.find_first_of("#;");
    if (comment_pos != std::string::npos) {
      line = line.substr(0, comment_pos);
    }

    if (line[0] == '[') {
      inSection=trim(line.substr(1,line.find(']')-1));
      continue;
    }

    posEqual=line.find('=');
    name  = trim(line.substr(0,posEqual));
    value = trim(line.substr(posEqual+1));

    content_[inSection+'/'+name]=Chameleon(value);
  }

  return true;
}

inline bool ConfigFile::Present(std::string const& section_list, std::string const& entry) const
{
  std::vector<std::string> sections;
  // Split into vector
  get_sections(section_list, sections);

  std::map<std::string,Chameleon>::const_iterator ci = content_.end();
  for ( std::vector<std::string>::const_iterator section = sections.begin(); section != sections.end(); ++section) {
     // look in each section in section_list
     ci = content_.find(*section + '/' + entry);
     // If found, then stop looking
     if (ci != content_.end()) break;
  }

  // If never found, then return false
  if (ci == content_.end()) return false;

  return true;
}

inline bool ConfigFile::SectionPresent(std::string const& section) const
{
   size_t size = section.size();

   if (size < 1) return false;

   for (std::map<std::string,Chameleon>::const_iterator ci = content_.begin(); ci != content_.end(); ++ci) {
      std::string test = ci->first.substr(0,size);
      // Find first entry that has this section
      if (section.compare(test)) return true;
   }
   return false;
}

inline Chameleon const& ConfigFile::Value(std::string const& section_list, std::string const& entry) const
{
  static Chameleon none("");

  std::vector<std::string> sections;
  // Split into vector
  get_sections(section_list, sections);

  std::map<std::string,Chameleon>::const_iterator ci = content_.end();
  for ( std::vector<std::string>::const_iterator section = sections.begin(); section != sections.end(); ++section) {
     // look in each section in section_list
     ci = content_.find(*section + '/' + entry);
     // If found, then stop looking
     if (ci != content_.end()) break;
  }

  // If never found, then return false

  if (ci == content_.end()) return none;
  //if (ci == content_.end()) throw "does not exist";

  return ci->second;
}

template <class T>
inline Chameleon const& ConfigFile::Value(std::string const& section_list, std::string const& entry, const T& value)
{
  //std::cout << "ConfigFile::Value(" << section_list << ", " << entry << ", " << value <<  ")" << std::endl;
  if (!Present(section_list, entry)) {
     std::vector<std::string> sections;
     // Split into vector
     get_sections(section_list, sections);
     // get the first (most specific) section in the list
     std::vector<std::string>::const_iterator section = sections.begin();
     // Insert the entry/value pair into the first section specified
     //std::cout << "Inserting: " << *section+'/'+entry << ": " << std::string(Chameleon(value)) << std::endl;
     return content_.insert(std::make_pair(*section+'/'+entry, Chameleon(value))).first->second;
  }
  else {
    return Value(section_list, entry);
  }
}

}

#endif
