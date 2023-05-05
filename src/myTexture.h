// #pragma once
// #include <map>
// #include "glm/fwd.hpp"
// #include "myProgram.h"
// #include "p6/p6.h"
// #include "tiny_obj_loader.h"

// class myTexture {
// private:


// public:
//     myTexture(const std::string& modelName)
//     {
//         // Diffuse
//         auto textureImage = p6::load_image_buffer("./models/" + modelName + "/" + modelName + ".jpg");
//         glGenTextures(1, &_diffuseTexture);
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, _diffuseTexture);
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, 0);

//         // MTL
//         loadMTL(modelName);
//     }

//     inline void activateTexture(const myProgram& program)
//     {
//         // std::cout<<"Texture\n";
//         glUniform1i(program.uTexture, 0);
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, _diffuseTexture);
//     }

//     inline void loadMTL(const std::string& modelName)
//     {
//         std::string                      warning, error;
//         std::vector<tinyobj::shape_t>    shapes;
//         std::vector<tinyobj::material_t> mtl;

//         // Load MTL file
//         std::string   mtl_filename = "./models/" + modelName + "/" + modelName + ".mtl";
//         std::ifstream ifs(mtl_filename);
//         if (!ifs.is_open())
//         {
//             std::cerr << "Failed to open file: " << mtl_filename << std::endl;
//             return;
//         }

//         tinyobj::LoadMtl(&mtl, &materials_map, &ifs, &warning, &error);
//         if (!warning.empty())
//         {
//             std::cout << "Warning: " << warning << std::endl;
//         }
//         if (!error.empty())
//         {
//             std::cerr << "Error: " << error << std::endl;
//             return;
//         }
//     }
// };