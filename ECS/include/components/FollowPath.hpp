/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FollowPath
*/

#include <vector>
#include <ostream>

/**
 * @brief components for the ECS, set the entity's FollowPath if it's an AI
 * 
 */
struct FollowPath {
    FollowPath() = default;

    /**
     * @brief parser for the config file
     * 
     * @param fileFollowPath 
     */
    void parse_follow_path_file(const std::string &fileFollowPath);

    /**
     * @brief Set the component object
     * 
     * @param fileFollowPath 
     */
    void set_component(const std::string &fileFollowPath);

    /**
     * @brief overload << operator
     * 
     * @param output , variable to fill for print the result of the function.
     * @param component class with the field to print. 
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const FollowPath &component) {
        output << "displaying checkpoint coords :" << std::endl;
        for(std::size_t i = 0; i < component._checkpoints.size(); ++i) {
            output << i << " :";
            for (std::size_t j = 0; j < component._checkpoints[i].size(); j += 1) {
                output << " " << component._checkpoints[i][j];
            }
            output << std::endl;
        }
        output << "Current checkpoint : " << component._currentCheckPoints;
        return output;
    }

    std::vector<std::vector<int16_t>> _checkpoints;
    uint16_t _currentCheckPoints;
};
