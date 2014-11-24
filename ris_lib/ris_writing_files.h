#pragma once

#include <functional>
#include <boost/filesystem.hpp>
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace ris {
    class write_to_temp_first_then_move {
        std::function<void(std::ostream&)> action;
        boost::filesystem::path temp_file;
        boost::filesystem::path target_file;
    public:
        template<typename TAction>
        write_to_temp_first_then_move(TAction a, std::string const& filename) :
            action(a),
            target_file(filename),
            temp_file(filename + "_")
        {}

        void start() {
            std::ofstream s(temp_file.generic_string());
            if (!s)
                throw std::runtime_error(std::string("cannot write ") + temp_file.generic_string());
            action(s);
            s.close();
            std::cout << "writing " << absolute(target_file).make_preferred().generic_string() << std::endl;
            rename(temp_file, target_file);
        }

        ~write_to_temp_first_then_move() {
            try {
                if (exists(temp_file))
                    remove(temp_file);
            }
            catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    };
}
