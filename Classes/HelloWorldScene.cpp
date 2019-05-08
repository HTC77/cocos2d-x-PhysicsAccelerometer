/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"


Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	auto world = scene->getPhysicsWorld();
	auto gravity = Vec2(0.0f, -198.0f);
	world->setGravity(gravity);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// enable Accelerometer
	Device::setAccelerometerEnabled(true);
	
	// acceleration listener
	auto accelerateListener = EventListenerAcceleration::create(
		CC_CALLBACK_2(HelloWorld::onAccelerated,this));
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		accelerateListener, this);

	// wall
	auto wall = Sprite::create();
	wall->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2));
	auto wallBody = PhysicsBody::createEdgeBox(visibleSize,
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	wall->setPhysicsBody(wallBody);
	this->addChild(wall);

	// ball
	auto ball = Sprite::create("ball.png");
	float radius = ball->getContentSize().width / 2;
	ball->setPosition(visibleSize / 2);
	auto ballBody = PhysicsBody::createCircle(radius,
		PhysicsMaterial(1.0, 0.8, 0.2));
	ballBody->setDynamic(true);
	ball->setPhysicsBody(ballBody);
	this->addChild(ball);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::onAccelerated(Acceleration* acceleration, Event* event)
{
	Vec2 gravity(acceleration->x * 120, acceleration->y * 120);
	_physicsWorld->setGravity(gravity);
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	_physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();

}
