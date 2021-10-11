#include "EntityManager.h"

#include "Constants.h"
#include "MotionSegment.h"
#include "MotionCurveFlyer.h"

// Motion
std::vector<MotionCurve*> flyerMotionCurves;
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
    std::shared_ptr<Material> shinyMaterial = addMaterial();
    shinyMaterial->initialize(1.0f, 32.0f);

    // *** Dull
    std::shared_ptr<Material> dullMaterial = addMaterial();
    dullMaterial->initialize(0.2f, 4.0f);

    // Create Entities

    // *** Flyer
    std::shared_ptr<Entity> flyer_entity = addEntity();
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
    std::shared_ptr<Entity> floater_entity = addEntity();
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
        1.0f, 1.0f, 1.0f, 0.0001f, 0.0001f, 0.0001f, 1.0f,
        MOTION_PLAN_TYPE_INFINITE, &floaterMotionSegments, nullptr);

    // *** Planet
    std::shared_ptr<Entity> planet_entity = addEntity();
    planet_entity->initialize(dullMaterial);
    //
    std::string planet_data = std::string("Mercury");
    Model* planet_model = planet_entity->getModel();
    planet_model->initialize(planet_data.c_str());
    planet_model->LoadModel();
    //
    MotionPlan* planetMotionPlan = planet_entity->getMotionPlan();
    planetMotionPlan->initialize(
        0.0f, -34.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 9.0f,
        1.0f, 1.0f, 1.0f, 0.02f, 0.02f, 0.02f, 2.0f,
        MOTION_PLAN_TYPE_FINITE, nullptr, nullptr);
}

void EntityManager::moveEntities()
{
    std::vector<std::shared_ptr<Entity>>::iterator itr = entityList.begin();
    for (; itr != entityList.end(); itr++)
    {
        (*itr)->moveEntity();
    }
}

void EntityManager::renderEntities(std::shared_ptr<Shader> shader)
{
    std::vector<std::shared_ptr<Entity>>::iterator itr = entityList.begin();
    for (; itr != entityList.end(); itr++)
    {
        (*itr)->renderEntity(shader);
    }
}

std::shared_ptr<Entity> EntityManager::addEntity()
{
    entityList.push_back(std::make_shared<Entity>());
    return entityList[entityList.size() - 1];
}

std::shared_ptr<Entity> EntityManager::getEntity(size_t index)
{
    std::shared_ptr<Entity> entity = nullptr;
    if (index < entityList.size())
    {
        entity = entityList[index];
    }
    return entity;
}

std::shared_ptr<Material> EntityManager::addMaterial()
{
    materialList.push_back(std::make_shared<Material>());
    return materialList[materialList.size() - 1];
}

std::shared_ptr<Material> EntityManager::getMaterial(size_t index)
{
    std::shared_ptr<Material> material = nullptr;
    if (index < materialList.size())
    {
        material = materialList[index];
    }
    return material;
}