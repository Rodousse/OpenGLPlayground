#include "engine/DataIO.hpp"

#include "engine/PerspectiveCamera.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <exception>
#include <unordered_map>

namespace engine
{
namespace IO
{
bool loadScene(const std::string& path, Scene& scene)
{
    Assimp::Importer importer{};
    const auto* aiScene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_PreTransformVertices);

    if(!aiScene)
    {
        throw std::runtime_error(std::string(__func__) + " : Could not load the file " + path);
    }

    if(aiScene->HasMeshes())
    {
        scene.meshes.resize(aiScene->mNumMeshes);

        for(decltype(aiScene::mNumMeshes) meshIndex = 0; meshIndex < aiScene->mNumMeshes; ++meshIndex)
        {
            auto& mesh = scene.meshes[meshIndex];
            mesh = std::make_shared<Mesh>();
            const auto* aiMesh = aiScene->mMeshes[meshIndex];
            mesh->name = std::string(aiMesh->mName.C_Str());
            mesh->vertices.resize(aiMesh->mNumVertices);
            mesh->faces.resize(aiMesh->mNumFaces);
            mesh->hasVertexNormals = aiMesh->HasNormals();

            decltype(aiMesh::mNumVertices) vertexIndex = 0;

            for(auto& vertex: mesh->vertices)
            {
                if(aiMesh->HasPositions())
                {
                    const auto& aiVertex = aiMesh->mVertices[vertexIndex];
                    vertex.pos = {aiVertex.x, aiVertex.y, aiVertex.z};
                }

                if(aiMesh->HasNormals())
                {
                    const auto& aiNormal = aiMesh->mNormals[vertexIndex];
                    vertex.normal = {aiNormal.x, aiNormal.y, aiNormal.z};
                    vertex.normal.normalize();
                }

                // consider only one uv set at the moment
                if(aiMesh->HasTextureCoords(0))
                {
                    const auto aiUV = aiMesh->mTextureCoords[vertexIndex][0];
                    vertex.uv = {aiUV.x, aiUV.y};
                }
                ++vertexIndex;
            }

            decltype(aiMesh::mNumFaces) faceIndex = 0;

            for(auto& face: mesh->faces)
            {
                const auto& aiFace = aiMesh->mFaces[faceIndex];

                for(std::size_t faceVertexIndex = 0; faceVertexIndex < face.indices.size(); ++faceVertexIndex)
                {
                    face.indices[faceVertexIndex] = aiFace.mIndices[faceVertexIndex];
                }

                const auto& ab = (mesh->vertices[face.indices[1]].pos - mesh->vertices[face.indices[0]].pos);
                const auto& ac = (mesh->vertices[face.indices[2]].pos - mesh->vertices[face.indices[0]].pos);

                face.normal = ab.cross(ac).normalized();
                ++faceIndex;
            }
            mesh->refreshBoundingBox();
        }
    }

    if(aiScene->HasCameras())
    {
        for(std::size_t camIndex = 0; camIndex < aiScene->mNumCameras; ++camIndex)
        {
            const auto* aiCamera = aiScene->mCameras[camIndex];
            aiNode* cameraNode = aiScene->mRootNode->FindNode(aiCamera->mName);
            aiMatrix4x4 cameraTransform = cameraNode->mTransformation;
            aiMatrix4x4 rotationMatrix = cameraTransform;
            rotationMatrix.a4 = rotationMatrix.b4 = rotationMatrix.c4 = 0.0f;
            rotationMatrix.d4 = 1.0f;
            std::shared_ptr<Camera> camera;

            if(!aiCamera)
            {
                continue;
            }

            if(aiCamera->mOrthographicWidth == 0.0f)
            {
                camera = std::make_shared<PerspectiveCamera>();
                auto* pCamera = dynamic_cast<PerspectiveCamera*>(camera.get());
                pCamera->setFovRad(aiCamera->mHorizontalFOV);
            }

            aiVector3D position = cameraTransform * aiCamera->mPosition;
            // camera->setPosition({aiCamera->mPosition.x, aiCamera->mPosition.y, aiCamera->mPosition.z});
            // camera->setPosition({position.x, position.y, position.z});
            camera->setNearClipPlane(aiCamera->mClipPlaneNear);
            camera->setFarClipPlane(aiCamera->mClipPlaneFar);

            aiVector3D up = rotationMatrix * aiCamera->mUp;
            up.Normalize();
            aiVector3D forward = rotationMatrix * aiCamera->mLookAt;
            forward.Normalize();
            scene.cameras.push_back(camera);

            camera->lookAt({position.x, position.y, position.z},
                           {forward.x, forward.y, forward.z},
                           {aiCamera->mUp.x, aiCamera->mUp.y, aiCamera->mUp.z});
        }
    }

    return true;
}

} // namespace IO

} // namespace engine
