#include "EntityManager.h"

#include "Constants.h"
#include "MotionSegment.h"
#include "MotionCurveFlyer.h"

// Motion
std::vector<MotionSegment> flyerMotionSegments {
    {   14 * FPS_WINDOW, 0, 
        true, DIRECTION_NEGATIVE, DIRECTION_NONE, DIRECTION_POSITIVE,
        false, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NONE, 
        false, DIRECTION_NONE
    },
    {   2 * FPS_WINDOW, 0, 
        true, DIRECTION_NEGATIVE, DIRECTION_NONE, DIRECTION_NONE,
        true, DIRECTION_NONE, DIRECTION_NEGATIVE, DIRECTION_NONE,
        false, DIRECTION_NONE
    },
    {   3 * FPS_WINDOW, 0, 
        true, DIRECTION_NEGATIVE, DIRECTION_NONE, DIRECTION_NEGATIVE,
        false, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NONE, 
        false, DIRECTION_NONE
    },
    {   1 * FPS_WINDOW, 0, 
        true, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NEGATIVE,
        true, DIRECTION_NONE, DIRECTION_NEGATIVE, DIRECTION_NONE,
        false, DIRECTION_NONE
    },
    {   8 * FPS_WINDOW, 0, 
        true, DIRECTION_POSITIVE, DIRECTION_NONE, DIRECTION_NEGATIVE,
        false, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NONE, 
        false, DIRECTION_NONE
    },
    {   1 * FPS_WINDOW, 0, 
        true, DIRECTION_POSITIVE, DIRECTION_NONE, DIRECTION_POSITIVE,
        true, DIRECTION_NONE, DIRECTION_NEGATIVE, DIRECTION_NONE,
        false, DIRECTION_NONE
    },
    {   2 * FPS_WINDOW, 0, 
        true, DIRECTION_POSITIVE, DIRECTION_NONE, DIRECTION_POSITIVE,
        false, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NONE, 
        false, DIRECTION_NONE
    },
    {   1 * FPS_WINDOW, 0, 
        true, DIRECTION_POSITIVE, DIRECTION_POSITIVE, DIRECTION_POSITIVE,
        true, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_POSITIVE,
        false, DIRECTION_NONE
    },
    {   1 * FPS_WINDOW, 0, 
        true, DIRECTION_POSITIVE, DIRECTION_POSITIVE, DIRECTION_POSITIVE,
        true, DIRECTION_NONE, DIRECTION_NEGATIVE, DIRECTION_NONE,
        false, DIRECTION_NONE
    },
    {   12 * FPS_WINDOW, 0, 
        true, DIRECTION_POSITIVE, DIRECTION_POSITIVE, DIRECTION_POSITIVE,
        false, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NONE, 
        false, DIRECTION_NONE
    },
};
//
std::vector<MotionCurve*> flyerMotionCurves;
//
std::vector<MotionSegment> floaterMotionSegments{
    {   0, 0,
        false, DIRECTION_NONE, DIRECTION_NONE, DIRECTION_NONE,
        true, DIRECTION_NEGATIVE, DIRECTION_POSITIVE, DIRECTION_NONE,
        false, DIRECTION_NONE
    }
};

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
    std::vector<MotionCurve*>::iterator itr_curve = flyerMotionCurves.begin();
    for (; itr_curve != flyerMotionCurves.end(); itr_curve++)
    {
        delete (*itr_curve);
        *itr_curve = nullptr;
    }
}

void EntityManager::initialize()
{
    // Create Materials

    // *** Shiny
    Material* shinyMaterial = addMaterial();
    shinyMaterial->initialize(1.0f, 32.0f);

    // *** Dull
    Material* dullMaterial = addMaterial();
    dullMaterial->initialize(0.2f, 4.0f);

    // Create Entities

    // *** Flyer
    Entity* flyer_entity = addEntity();
    flyer_entity->initialize(shinyMaterial);
    //
    std::string flyer_data = std::string("Viper-mk-IV-fighter");
    Model* flyer_model = flyer_entity->getModel();
    flyer_model->initialize(flyer_data.c_str());
    flyer_model->LoadModel();
    //
    MotionCurveFlyer* motionCurveFlyer = new MotionCurveFlyer();
    flyerMotionCurves.push_back(motionCurveFlyer);
    //
    MotionPlan* flyerMotionPlan = flyer_entity->getMotionPlan();
    flyerMotionPlan->initialize(
        25.0f, 1.0f, -20.0f,
        0.0f, 55.0f, -10.0f, 0.2f,
        0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 1.0f,
        MOTION_PLAN_TYPE_REPEAT, nullptr, &flyerMotionCurves);

    // *** Floater
    Entity* floater_entity = addEntity();
    floater_entity->initialize(dullMaterial);
    //
    std::string floater_data = std::string("UHFSatcom");
    Model* floater_model = floater_entity->getModel();
    floater_model->initialize(floater_data.c_str());
    floater_model->LoadModel();
    //
    MotionPlan* floaterMotionPlan = floater_entity->getMotionPlan();
    floaterMotionPlan->initialize(
        -2.3f, 1.0f, -4.7f,
        0.0f, 0.0f, 45.0f, 0.75f,
        1.0f, 1.0f, 1.0f, 0.02f, 0.02f, 0.02f, 1.0f,
        MOTION_PLAN_TYPE_INFINITE, &floaterMotionSegments, nullptr);
}

void EntityManager::moveEntities()
{
    std::vector<std::unique_ptr<Entity>>::iterator itr = entityList.begin();
    for (; itr != entityList.end(); itr++)
    {
        (*itr)->moveEntity();
    }
}

void EntityManager::renderEntities(Shader* shader)
{
    std::vector<std::unique_ptr<Entity>>::iterator itr = entityList.begin();
    for (; itr != entityList.end(); itr++)
    {
        (*itr)->renderEntity(shader);
    }
}

Entity* EntityManager::addEntity()
{
    entityList.push_back(std::make_unique<Entity>());
    return &(*(entityList[entityList.size() - 1]));
}

Material* EntityManager::addMaterial()
{
    materialList.push_back(std::make_unique<Material>());
    return &(*(materialList[materialList.size() - 1]));
}

Material* EntityManager::getMaterial(size_t index)
{
    Material* material = nullptr;
    if (index < materialList.size())
    {
        material = &(*(materialList[index]));
    }
    return material;
}