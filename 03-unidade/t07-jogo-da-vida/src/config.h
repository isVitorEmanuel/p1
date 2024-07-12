#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "../init/ini_parser.h"
#include "../lib/canvas.h"

using namespace life;

/*!
 * This class functions to set all the initialization information 
 * for the simulation.
 */
class Config {
public:

	//=== Members. 
	/// Set input_cfg.
	std::string set_input_cfg(IniParser &filename);
	/// Set number of max_gen.
	size_t set_max_gen(IniParser &filename);
	/// Set bool of genetare_image.
	bool set_generate_image(IniParser &filename);
	/// Set color of alive cells.
	Color set_alive_color(IniParser &filename);
	/// Set background color.
	Color set_bkg_color(IniParser &filename);
	/// Set block size.
	size_t set_block_size(IniParser &filename);
	/// Set path.
	std::string set_path(IniParser &filename);
	/// Set fps.
	int set_fps(IniParser &filename);
	/// Set all members with others methods.
	void load(const std::string &filename);

	//=== Attribute accessors members.
	/// Get input_cfg.
	std::string get_input_cfg() { return input_cfg; }
	/// Get number of max_gen.
	size_t get_max_gen() { return max_gen; }
	/// Get bool of genetare_image.
	bool get_generate_image() { return generate_image; }
	/// Get color of alive cells.
	Color get_alive_color() { return alive_color; }
	/// Get background color.
	Color get_bkg_color() { return bkg_color; }
	/// Get block size.
	size_t get_block_size() { return block_size; }
	/// Get path.
	std::string get_path() { return path; }
	/// Get fps.
	int get_fps() { return fps; }
	
	//=== Auxiliary functions.
	/// Remove quotes of the paths.
	void remove_quotes(std::string& path);

private:
	std::string input_cfg;   //!< The file where the simulation grid configuration is located.
	size_t max_gen;          //!< Maximum number of generations for the simulation.
	bool generate_image;     //!< Boolean indicating whether simulation images will be generated.
	Color alive_color;       //!< Color of alive cell in image.
	Color bkg_color;         //!< Color of background in image.
	size_t block_size;       //!< Pixel size of each cell.
	std::string path;        //!< The directory where the images will be saved.
	int fps;                 //!< Display output speed
};

#endif // CONFIG_H