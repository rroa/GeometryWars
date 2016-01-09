#include "Utility/package.hpp"

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "BlackHole.hpp"

#include "EnemySpawner.hpp"
#include "PlayerShip.hpp"

#include "EntityManager.hpp"

#include <iostream>
#include <algorithm>

//---------------------------------------------------------------------------------
// Written by Terence J. Grant - tjgrant [at] tatewake [dot] com
// Find the full tutorial at: http://gamedev.tutsplus.com/series/
//----------------------------------------------------------------------------------

namespace
{
    bool NeedsCleanup( Entity* actor )
    {
        return actor->isExpired();
    }
}

void EntityManager::KillPlayer()
{
    PlayerShip::getInstance()->kill();

    for (std::list<Enemy*>::iterator j = mEnemies.begin(); j != mEnemies.end(); j++)
    {
        (*j)->wasShot();
    }

    for (std::list<BlackHole*>::iterator j = mBlackHoles.begin(); j != mBlackHoles.end(); j++)
    {
        (*j)->kill();
    }

    EnemySpawner::getInstance()->reset();
}

EntityManager::EntityManager()
: mIsUpdating(false)
{

}

int EntityManager::getCount() const
{
    return (int)mEntities.size();
}

int EntityManager::getBlackHoleCount() const
{
    return (int)mBlackHoles.size();
}

std::list<BlackHole*> EntityManager::getBlackHoles() const
{
    return mBlackHoles;
}

void EntityManager::add(Entity* entity)
{
    if (!mIsUpdating)
    {
        addEntity(entity);
    }
    else
    {
        mAddedEntities.push_back(entity);
    }
    //mAddedEntities.push_back(entity);
}

void EntityManager::addEntity(Entity* entity)
{
    mEntities.push_back(entity);

    switch (entity->getKind())
    {
        case Entity::kBullet:       mBullets.push_back((Bullet*)entity); break;
        case Entity::kEnemy:        mEnemies.push_back((Enemy*)entity); break;
        case Entity::kBlackHole:    mBlackHoles.push_back((BlackHole*)entity); break;

        default: break;
    }
}

void EntityManager::deleteEntity(Entity* entity)
{
    // Just in case :P
    if(!entity) return;

    // Retrieve actor from entities list
    //
    std::list<Entity*>::iterator entityResult = std::find( mEntities.begin(), mEntities.end(), entity );

    // Retrieve entity from enemies list
    //
    std::list<Enemy*>::iterator enemyResult = std::find( mEnemies.begin(), mEnemies.end(), entity );

    // Retrieve entity from bullets list
    //
    std::list<Bullet*>::iterator bulletsResult = std::find( mBullets.begin(), mBullets.end(), entity );

    // Retrieve entity from bullets list
    //
    std::list<BlackHole*>::iterator blackholeResult = std::find( mBlackHoles.begin(), mBlackHoles.end(), entity );

    // Deleting entity iterator from lists
    //
    if( mEntities.size() > 0 && entityResult != mEntities.end() )
    {
        mEntities.erase( entityResult );
    }

    if( mEnemies.size() > 0 && enemyResult != mEnemies.end() )
    {
        mEnemies.erase( enemyResult );
    }

    if( mBullets.size() > 0 && bulletsResult != mBullets.end() )
    {
        mBullets.erase( bulletsResult );
    }

    if( mBlackHoles.size() > 0 && blackholeResult != mBlackHoles.end() )
    {
        mBlackHoles.erase( blackholeResult );
    }

    // Removing the allocated pointer
    //
    delete entity;
}

void EntityManager::CleanUp()
{
    std::list<Entity*>::iterator t = std::find_if ( mEntities.begin(), mEntities.end(), NeedsCleanup );
    if(t != mEntities.end() )
    {
        deleteEntity( *t );
    }
}

void EntityManager::update()
{
    mIsUpdating = true;

    handleCollisions();

    for(std::list<Entity*>::iterator iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        (*iter)->update();
    }

    CleanUp();

    mIsUpdating = false;

    for(std::vector<Entity*>::iterator iter = mAddedEntities.begin(); iter != mAddedEntities.end(); iter++)
    {
        addEntity(*iter);
    }

    mAddedEntities.clear();

}

void EntityManager::handleCollisions()
{
    for (std::list<Enemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); i++)
    {
        for (std::list<Enemy*>::iterator j = mEnemies.begin(); j != mEnemies.end(); j++)
        {
            if (isColliding(*i, *j))
            {
                (*i)->handleCollision(*j);
                (*j)->handleCollision(*i);
            }
        }
    }

    // handle collisions between bullets and enemies
    for (std::list<Enemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); i++)
    {
        for (std::list<Bullet*>::iterator j = mBullets.begin(); j != mBullets.end(); j++)
        {
            if (isColliding(*i, *j))
            {
                (*i)->wasShot();
                (*j)->setExpired();
            }
        }
    }

    // handle collisions between the player and enemies
    for (std::list<Enemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); i++)
    {
        if ((*i)->getIsActive() && isColliding(PlayerShip::getInstance(), *i))
        {
            KillPlayer();
            break;
        }
    }

    // handle collisions with black holes
    for (std::list<BlackHole*>::iterator i = mBlackHoles.begin(); i != mBlackHoles.end(); i++)
    {
        for (std::list<Enemy*>::iterator j = mEnemies.begin(); j != mEnemies.end(); j++)
        {
            if ((*j)->getIsActive() && isColliding(*i, *j))
            {
                (*j)->wasShot();
            }
        }

        for (std::list<Bullet*>::iterator j = mBullets.begin(); j != mBullets.end(); j++)
        {
            if (isColliding(*i, *j))
            {
                (*j)->setExpired();
                (*i)->wasShot();
            }
        }

        if (isColliding(PlayerShip::getInstance(), *i))
        {
            KillPlayer();
            break;
        }
    }
}

bool EntityManager::isColliding(Entity* a, Entity* b)
{
    float radius = a->getRadius() + b->getRadius();
    return !a->isExpired() && !b->isExpired() && a->getPosition().distanceSquared(b->getPosition()) < radius * radius;
}

void EntityManager::draw(tSpriteBatch* spriteBatch)
{
    for(std::list<Entity*>::iterator iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        (*iter)->draw(spriteBatch);
    }
}

std::list<Entity*> EntityManager::getNearbyEntities(const tPoint2f& pos, float radius)
{
    std::list<Entity*> result;
    for(std::list<Entity*>::iterator iter = mEntities.begin(); iter != mEntities.end(); iter++)
    {
        if (*iter)
        {
            if (pos.distanceSquared((*iter)->getPosition()) < radius * radius)
            {
                result.push_back(*iter);
            }
        }
    }

    return result;
}

