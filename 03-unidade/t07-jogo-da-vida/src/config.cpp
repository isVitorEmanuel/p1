#include <stdexcept>
#include <iostream>

#include "config.h"

/*! This function remove quotes of the paths.
 * @param path File path from which the quotes will be removed.
 */
void Config::remove_quotes(std::string& path) {
    size_t start = 0;
    size_t end = path.size() - 1;

    // Check if the first or last character is a quote.
    if (path.front() == '\"') { start = 1; }
    if (path.back() == '\"') { end = path.size() - 2; }

    // Modify the original string to remove the leading and trailing quotes.
    path = path.substr(start, end - start + 1);
}

// === Members === 
/*!
* This function set the input informed by glife.ini.
* @param filename Name of the config file.
* @return The file input.
*/
std::string Config::set_input_cfg(IniParser &filename) {
    std::string input; //!<- String of the name of input.
    bool informed = filename.get_string("", "input_cfg", input);  //!<- Show if the data was provided.

	/// Check if input was be informed.    
    if(!informed) {
        throw std::runtime_error("The < input_cfg > not be informed in [config/glife.ini]");
    }

    remove_quotes(input);

    return input;
}

/*!
* This function set the max number of generations of simulation.
* @param filename Name of the config file.
* @return max number of generations.
*/
size_t Config::set_max_gen(IniParser &filename) {
    int number_gen; 
    bool informed = filename.get_int("", "max_gen", number_gen);  //!<- Show if the data was provided.

	/// Check if the number of gens is unlimited.
	if(!informed || number_gen == 0) {
		std::cout << ">>> The number of generations is unlimited because max_gen was either omitted or is equal to 0." << std::endl;
        number_gen = 0;
	}

    if(number_gen < 0) {
        throw std::invalid_argument("Used a negative value in < max_gen > when a positive integer or zero was expected.");
    }

	return number_gen;
}

/*!
* This function set if the user wants to generate images; by default, this value is true.
* @param filename Name of the config file.
* @return Boolean indicating whether the user wants to generate images or not.
*/
bool Config::set_generate_image(IniParser &filename) {
    bool gen = true;
    bool informed = filename.get_bool("Image", "generate_image", gen);   //!<- Show if the data was provided.
    
    if(!informed) {
        std::cout << ">>> The value < generate_image > was not provided. Using the default value [true]." << std::endl;
    }
    
    return gen;
}

/*!
* This function set the color of alive cells.
* @param filename Name of the config file.
* @return Color of alive cells.
*/
Color Config::set_alive_color(IniParser &filename) {
    std::vector<std::string> colors = {
        "black", "white", "dark_green", "red", "green", "blue", "crimson", 
        "light_blue", "light_grey", "deep_sky_blue", "dodger_blue", 
        "steel_blue", "yellow", "light_yellow"
    };  //!<- Vector with all colors.

    std::string color;
    bool informed = filename.get_string("Image", "alive", color); //!<- Show if the data was provided.

    /// Convert the string of color to lowercase to use in map "color_pallet".
    std::transform(color.begin(), color.end(), color.begin(), ::tolower);

    /// Check if the color was informed or is valid.
    if (!informed || std::find(colors.begin(), colors.end(), color) == colors.end()) {

        if(!informed) { std::cout << ">>> The < alive > not informed in [config/glife.ini]." << std::endl; } 
        else { std::cout << ">>> The color < " << color << " > is not a valid color." << std::endl; }
        
        std::cout << ">>> Using the default value [BLUE]." << std::endl;
    
        /// Set the default color.
        color = "blue";
    }

    return color_pallet[color];
}

/*!
* This function set the color of deth cells.
* @param filename Name of the config file.
* @return Color of backgrond.
*/
Color Config::set_bkg_color(IniParser &filename) {
    std::vector<std::string> colors = {
        "black", "white", "dark_green", "red", "green", "blue", "crimson", 
        "light_blue", "light_grey", "deep_sky_blue", "dodger_blue", 
        "steel_blue", "yellow", "light_yellow"
    };  //!<- Vector with all colors.

    std::string color; 
    bool informed = filename.get_string("Image", "bkg", color);  //!<- Show if the data was provided.

    /// Convert the string of color to lowercase to use in map "color_pallet".
    std::transform(color.begin(), color.end(), color.begin(), ::tolower);

    /// Check if the color was informed or is valid.
    if (!informed || std::find(colors.begin(), colors.end(), color) == colors.end()) {
        
        if (!informed) { std::cout << ">>> The < bkg > not informed in [config/glife.ini]." << std::endl; } 
        else { std::cout << ">>> The color < " << color << " > is not a valid color." << std::endl; }
        std::cout << ">>> Using the default value [YELLOW]." << std::endl;

        /// Set the default color.
        color = "yellow";
    }
 
    return color_pallet[color];
}

/*!
* This function set the path where the images will be saved.
* @param filename Name of the config file.
* @return Path of directory.
*/
size_t Config::set_block_size(IniParser &filename) {
    int b_size;
    bool informed = filename.get_int("Image", "block_size", b_size); //!<- Show if the data was provided.
    
    /// Check if the color was informed.
    if (!informed) { 
        std::cout << ">>> The < block_size > not informed in [config/glife.ini]." << std::endl;
        std::cout << ">>> Using the default value [10]." << std::endl;
        b_size = 10;
    }

    if(b_size <= 0) {
        throw std::invalid_argument("Used a negative value or zero in < block_size > when a positive integer was expected.");
    }

    return static_cast<size_t>(b_size);
}

/*!
* This function set the path of the directory where the images will be saved..
* @param filename Name of the config file.
* @return The directory.
*/
std::string Config::set_path(IniParser &filename) {
	std::string file_imgs;
    bool informed = filename.get_string("Image", "path", file_imgs);  //!<- Show if the data was provided.

	/// Check if input was be informed.
    if (!informed) {
        throw std::runtime_error("The < path > not be informed in [config/glife.ini]");
    }

    remove_quotes(file_imgs);

    return file_imgs;
}

/*!
* This function set the number of frames per second; by default, this value is 2.
* @param filename Name of the config file.
* @return Nuber of fps.
*/
int Config::set_fps(IniParser &filename) {
    int fps;
    bool informed = filename.get_int("Text", "fps", fps);  //!<- Show if the data was provided.

    /// Check if input was be informed.
    if(!informed) {
        std::cout << ">>> The < fps > not informed in [config/glife.ini]." << std::endl;
        std::cout << ">>> Using the default value [2]." << std::endl;
        fps = 2;
    }

    if(fps <= 0) {
        throw std::invalid_argument("Used a negative value or zero in < fps > when a positive integer was expected.");
    }

    return fps;
}

/*!
* This function use others functions to set all members class.
* @param filename Name of the config file.
*/
void Config::load(const std::string &filename) {
	IniParser reader;

	if (!reader.load(filename)) {
		throw std::runtime_error(">>> Failed to load or parse the config file.");
	}

	// Set the global configuration.
	input_cfg = set_input_cfg(reader);
	max_gen = set_max_gen(reader);

	// Set image configurations.
	generate_image = set_generate_image(reader);
	alive_color = set_alive_color(reader);
	bkg_color = set_bkg_color(reader);
	block_size = set_block_size(reader);
	path = set_path(reader);

	// Set text configuration.
	fps = set_fps(reader);

    std::cout << ">>> File [ " << filename << " ] read successfully!" << std::endl;
}