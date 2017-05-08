/**
\mainpage About this Project
This project aims at making a Rube Goldberg Machine in the Box2D environment
We intend to create a Rube Goldberg machine simulation in the Box2D platform
The idea is to use the inbuilt physics provided by the Box2D physics engine to demonstrate a
Rube Goldberg Machine
It will contain several moving objects which will follow the laws of Physics provided by Box2D
There will be balls, dominos, moving planks, and other interesting objects, including ropes and
candles
The idea is to learn to implement both physics and graphics in the traditional language : C++
We have been working on this project since past 1 month or so and we learnt a lot in due course
of time
@author byters group 11 (Anmol Arora - 13000027 , Pranjal Khare - 130050028 , Aman Goel - 130050041)
@bug write about the bugs
* As such there are no so called "bugs"
* The project is currently only partially built so the machine is not exptected to work as desired
* Some (rather many) features won't work as desired
* The candle has not been implemented yet
* The idea was to create a figure of "Group 11" using the rods. But it has not been implemented yet
*/

#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;
#include "dominos.hpp"

namespace cs251 {
	dominos_t::dominos_t() {
		
		//!Ground -----------------------------------------------------------------------------------------------------------------------------------------
		//! This code below describes the properties of the ground
		//! It tell us about the location of the ground
		//! the ground lies at the bottom of the screen
		//! all the active region is above the ground
		b2Body* ground; {
			b2EdgeShape shape; 
			shape.Set(b2Vec2(-90.0f, -5.0f), b2Vec2(90.0f, -5.0f));
			b2BodyDef bd; 
			ground = m_world->CreateBody(&bd); 
			ground->CreateFixture(&shape, 0.0f);
		}
		
		//!Top left most horizontal and inclined shelves --------------------------------------------------------------------------------------------------
		//! This is the upper-left section of the screen
		//! Here we make a horizotnal plank and another inclined plank
		{
			b2PolygonShape plank;
			plank.SetAsBox(6.0f, 0.25f);	
			b2BodyDef bd;
			bd.position.Set(-27.0f, 30.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank_inclined;
			plank_inclined.SetAsBox(3.0f, 0.25f);	
			b2BodyDef bd;
			bd.position.Set(-19.5f, 27.4f);
			bd.angle = -0.3f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank_inclined, 0.0f);
		}
		
		//!Top right horizontal shelf ---------------------------------------------------------------------------------------------------------------------
		//! This is the upper-right section of the screen
		//! Here we make a horizontal plank
		{
			b2PolygonShape plank;
			plank.SetAsBox(6.0f, 0.25f);	
			b2BodyDef bd;
			bd.position.Set(13.0f, 40.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		
		//!The chain of dominos on the right plank --------------------------------------------------------------------------------------------------------
		//! The dominos on the right plank
		//! This part includes the sequence of dominos that are present on the plank on the upper right corner of the screen
		//! The pendulum knocks off the domino on the extreme right and then a chain reaction starts
		{
			b2PolygonShape dominos;
			dominos.SetAsBox(0.1f, 1.0f);	
			b2FixtureDef dominos_fixture;
			dominos_fixture.shape = &dominos;
			dominos_fixture.density = 20.0f;
			dominos_fixture.friction = 0.1f;
			for (int i = 0; i < 10; ++i) {
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(17.5f - 1.0f * i, 41.25f);
				b2Body* body = m_world->CreateBody(&bd);
				body->CreateFixture(&dominos_fixture);
			}
		}
		
		//!The chain of planks below the top left plank ---------------------------------------------------------------------------------------------------
		//! This part includes the code for the series of planks on the right of the screen
		//! These planks provide direction as well as momentum to the ball
		{
			b2PolygonShape plank;
			plank.SetAsBox(4.0f, 0.25f, b2Vec2(-30.f,20.f), 0.0f);
			b2BodyDef bd;
			bd.position.Set(10.5f, 0.0f);
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(3.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-13.5f, 22.7f);
			bd.angle = 0.3f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(2.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-24.2f, 18.2f);
			bd.angle = 0.45f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(2.4f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-27.2f, 16.5f);
			bd.angle = 0.0f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.8f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-29.6f, 18.2f);
			bd.angle = 0.5f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		
		//!The box ----------------------------------------------------------------------------------------------------------------------------------------
		//! The ball coming from the right collides with the box and knocks it into the cavity
		//! Another ball occupies the small gap to the right of the box and hence provides a path for the other 2 balls
		{
			b2PolygonShape box;
			box.SetAsBox(2.0f, 1.5f);
			b2BodyDef bd3;
			bd3.position.Set(-17.5f, 22.0f);
			bd3.type = b2_dynamicBody;
			b2Body* body3 = m_world->CreateBody(&bd3);
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 0.1f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &box;
			body3->CreateFixture(fd3);
		}
		
		//!The pendulum on the right that knocks the dominos off ------------------------------------------------------------------------------------------
		//! This pendulum is responsible for knocking the right most domino which creates a chain reaaction
		//! The dominos fall one by one and ultimately hit the ball which then bounces to the left
		{
			b2Body* b2;
			{
				b2PolygonShape thread;
				thread.SetAsBox(0.25f, 1.5f);  
				b2BodyDef bd;
				bd.position.Set(18.0f, 38.0f); //end of thread
				b2 = m_world->CreateBody(&bd);
				b2->CreateFixture(&thread, 10.0f);
			}
			b2Body* b4;
			{
				b2CircleShape bob;
				bob.m_radius = 0.5; //size of pendulum
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(21.0f, 42.0f); //coordinates of bob of pendulum
				b4 = m_world->CreateBody(&bd);
				b4->CreateFixture(&bob, 2.0f);
			}
			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(18.0f, 50.0f); //position of the point of suspension
			jd.Initialize(b2, b4, anchor);
			m_world->CreateJoint(&jd);
		}
		
		//!The pendulums on the left that knock the dominos off -------------------------------------------------------------------------------------------
		//! This section includes the code for a series of pendulums which hit the left ball and provide momentum to the other ball
		{
			for(int i = 0 ; i < 5 ; i++) {
				b2Body* b2;
				{
					b2PolygonShape thread;
					thread.SetAsBox(0.25f, 1.5f);
					b2BodyDef bd;
					bd.position.Set(-32.0f + i, 28.0f); //end of thread
					b2 = m_world->CreateBody(&bd);
					b2->CreateFixture(&thread, 10.0f);
				}
				b2Body* b4;
				{
					b2CircleShape bob;
					bob.m_radius = 0.5; //size of pendulum
					b2BodyDef bd;
					bd.type = b2_dynamicBody;
					if(i == 0)
						bd.position.Set(-38.0f + i, 34.0f);//coordinates of bob of pendulum
					else
						bd.position.Set(-32.0f + i, 31.0f); //coordinates of bob of pendulum
					b4 = m_world->CreateBody(&bd);
					b4->CreateFixture(&bob, 2.0f);
				}
				b2RevoluteJointDef jd;
				b2Vec2 anchor;
				anchor.Set(-32.0f + i, 40.0f); //position of the point of suspension
				jd.Initialize(b2, b4, anchor);
				m_world->CreateJoint(&jd);
			}
		}
		
		//!The pair of balls on the upper left plank ------------------------------------------------------------------------------------------------------
		//! These 2 balls are present on the left plank
		//! One of these balls moves on the top of the box and goes down ultimately
		{
			b2Body* ball_1;
			b2CircleShape circle;
			circle.m_radius = 0.5;
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 0.5f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(-27.0f, 31.0f); //coordinates here
			ball_1 = m_world->CreateBody(&ballbd);
			ball_1->CreateFixture(&ballfd);
		}
		{
			b2Body* ball_2;
			b2CircleShape circle;
			circle.m_radius = 0.5;
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 0.5f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(-22.0f, 31.0f); //coordinates here
			ball_2 = m_world->CreateBody(&ballbd);
			ball_2->CreateFixture(&ballfd);
		}
		
		//!The ball on the upper right plank --------------------------------------------------------------------------------------------------------------
		//! This is the ball present on the upper right plank
		//! This ball is ultimately responsible for hitting the box and knocking it into the cavity
		{
			b2Body* ball;
			b2CircleShape circle;
			circle.m_radius = 0.5;
			b2FixtureDef ballfd;
			ballfd.shape = &circle;
			ballfd.density = 1.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef ballbd;
			ballbd.type = b2_dynamicBody;
			ballbd.position.Set(8.0f, 41.0f); //coordinates heres
			ball = m_world->CreateBody(&ballbd);
			ball->CreateFixture(&ballfd);
		}
		
		//!The (apparently) curved part -------------------------------------------------------------------------------------------------------------------
		//! This is the path which gives direction and momentum to the oncoming ball so that the chain reaction continues
		{
			b2PolygonShape plank;
			plank.SetAsBox(3.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-32.0f, 18.25f);
			bd.angle = 0.5f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(2.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-30.8f, 13.75f);
			bd.angle = -0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(3.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-26.5f, 12.35f);
			bd.angle = 0.0f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-22.4f, 12.75f);
			bd.angle = 0.1f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		
		//!The funnel structure ---------------------------------------------------------------------------------------------------------------------------
		//! The funnel structure helps the ball to move down
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-20.8f, 12.5f);
			bd.angle = -0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-17.8f, 12.5f);
			bd.angle = 0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-20.3f, 10.5f);
			bd.angle = 0.5f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-18.5f, 11.0f);
			bd.angle = 0.5f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-19.7f, 8.7f);
			bd.angle = -0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(2.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-17.1f, 8.0f);
			bd.angle = 0.0f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(2.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-15.0f, 6.0f);
			bd.angle = 0.0f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-12.2f, 7.0f);
			bd.angle = 0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		{
			b2PolygonShape plank;
			plank.SetAsBox(1.0f, 0.25f);
			b2BodyDef bd;
			bd.position.Set(-17.0f, 7.0f);
			bd.angle = 0.5f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		
		//The (apparent) candle --------------------------------------------------------------------------------------------------------------------------
		{
			b2PolygonShape candle;
			candle.SetAsBox(0.3f, 2.0f);	
			b2FixtureDef fd;
			fd.shape = &candle;
			fd.density = 0.2f;
			fd.friction = 0.1f;
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-13.5f, 7.75f);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&fd);
		}
		
		//!The pendulum which gets broken by the candle ---------------------------------------------------------------------------------------------------
		//! This pendulum waits for the candle to burn its thread so that the bob of the pendulum falls on the see-saw
		{
			b2Body* b2;
			{
				b2PolygonShape thread;
				thread.SetAsBox(0.25f, 1.5f);  
				b2BodyDef bd;
				bd.position.Set(-11.0f, 13.0f); //end of thread
				b2 = m_world->CreateBody(&bd);
				b2->CreateFixture(&thread, 10.0f);
			}
			b2Body* b4;
			{
				b2CircleShape bob;
				bob.m_radius = 0.5; //size of pendulum
				b2BodyDef bd;
				bd.type = b2_dynamicBody;
				bd.position.Set(-11.0f, 6.0f); //coordinates of bob of pendulum
				b4 = m_world->CreateBody(&bd);
				b4->CreateFixture(&bob, 2.0f);
			}
			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(-11.0f, 13.0f); //position of the point of suspension
			jd.Initialize(b2, b4, anchor);
			m_world->CreateJoint(&jd);
		}
		
		//!The see-saw system at the bottom ---------------------------------------------------------------------------------------------------------------
		//! The see-saw system starts to work when the bob of the pendulum falls on it
		//! The box bounces and falls on the bucket
		{
			//!The triangle wedge
			//! This triangle acts as pivot
			b2Body* wedge;
			b2PolygonShape poly;
			b2Vec2 vertices[3];
			vertices[0].Set(-1,0);
			vertices[1].Set(1,0);
			vertices[2].Set(0,1.5);
			poly.Set(vertices, 3);
			b2FixtureDef wedgefd;
			wedgefd.shape = &poly;
			wedgefd.density = 10.0f;
			wedgefd.friction = 0.0f;
			wedgefd.restitution = 0.0f;
			b2BodyDef wedgebd;
			wedgebd.position.Set(-18.0f, -5.0f);
			wedge = m_world->CreateBody(&wedgebd);
			wedge->CreateFixture(&wedgefd);

			//!The plank on top of the wedge
			//! This is the supporting bar of the see-saw
			b2PolygonShape plank_on_wedge;
			plank_on_wedge.SetAsBox(8.0f, 0.2f);
			b2BodyDef bd2;
			bd2.position.Set(-18.0f, -4.0f);
			bd2.type = b2_dynamicBody;
			b2Body* body = m_world->CreateBody(&bd2);
			b2FixtureDef *fd2 = new b2FixtureDef;
			fd2->density = 1.f;
			fd2->shape = new b2PolygonShape;
			fd2->shape = &plank_on_wedge;
			body->CreateFixture(fd2);

			b2RevoluteJointDef jd;
			b2Vec2 anchor;
			anchor.Set(-18.0f, -4.0f);
			jd.Initialize(wedge, body, anchor);
			m_world->CreateJoint(&jd);

			//!The light box on the right side of the see-saw
			//! The box on the see-saw
			b2PolygonShape box;
			box.SetAsBox(1.0f, 1.0f);
			b2BodyDef bd3;
			bd3.position.Set(-24.0f, -3.0f);
			bd3.type = b2_dynamicBody;
			b2Body* body3 = m_world->CreateBody(&bd3);
			b2FixtureDef *fd3 = new b2FixtureDef;
			fd3->density = 0.01f;
			fd3->shape = new b2PolygonShape;
			fd3->shape = &box;
			body3->CreateFixture(fd3);
		}
		
		//!The pulley system on the left ------------------------------------------------------------------------------------------------------------------
		//! This pulley system starts to work when the box falls in the bucket
		//! The bar on the left rises to create a 1 (one)
		{
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(-6,2);
			bd->fixedRotation = true;
			
			//The open box
			b2FixtureDef *part_1 = new b2FixtureDef;
			part_1->density = 10.0;
			part_1->friction = 0.5;
			part_1->restitution = 0.f;
			part_1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
			part_1->shape = &bs1;
			b2FixtureDef *part_2 = new b2FixtureDef;
			part_2->density = 10.0;
			part_2->friction = 0.5;
			part_2->restitution = 0.f;
			part_2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
			part_2->shape = &bs2;
			b2FixtureDef *part_3 = new b2FixtureDef;
			part_3->density = 10.0;
			part_3->friction = 0.5;
			part_3->restitution = 0.f;
			part_3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
			part_3->shape = &bs3;
			 
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(part_1);
			box1->CreateFixture(part_2);
			box1->CreateFixture(part_3);

			//The bar
			bd->position.Set(10,-2.5);	
			part_1->density = 30.0;	  
			b2Body* box2 = m_world->CreateBody(bd);
			box2->CreateFixture(part_1);

			// The pulley joint
			b2PulleyJointDef* myjoint = new b2PulleyJointDef();
			b2Vec2 worldAnchorOnBody1(-6, 5); // Anchor point on body 1 in world axis
			b2Vec2 worldAnchorOnBody2(10, 5); // Anchor point on body 2 in world axis
			b2Vec2 worldAnchorGround1(-6, 5); // Anchor point for ground 1 in world axis
			b2Vec2 worldAnchorGround2(10, 5); // Anchor point for ground 2 in world axis
			float32 ratio = 1.0f; // Define ratio
			myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
			m_world->CreateJoint(myjoint);
		}
		
		//!The pulley system on the right -----------------------------------------------------------------------------------------------------------------
		//! The pulley system on the right becomes active when the balls on the left fall into the bucket
		//! The bar on the left rises to create a 1 (one)
		//! The 2 rising bars create a "11" (group 11)
		{
			b2BodyDef *bd = new b2BodyDef;
			bd->type = b2_dynamicBody;
			bd->position.Set(29,2);
			bd->fixedRotation = true;
			
			//The open box
			b2FixtureDef *part_1 = new b2FixtureDef;
			part_1->density = 10.0;
			part_1->friction = 0.5;
			part_1->restitution = 0.f;
			part_1->shape = new b2PolygonShape;
			b2PolygonShape bs1;
			bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
			part_1->shape = &bs1;
			b2FixtureDef *part_2 = new b2FixtureDef;
			part_2->density = 10.0;
			part_2->friction = 0.5;
			part_2->restitution = 0.f;
			part_2->shape = new b2PolygonShape;
			b2PolygonShape bs2;
			bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
			part_2->shape = &bs2;
			b2FixtureDef *part_3 = new b2FixtureDef;
			part_3->density = 10.0;
			part_3->friction = 0.5;
			part_3->restitution = 0.f;
			part_3->shape = new b2PolygonShape;
			b2PolygonShape bs3;
			bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
			part_3->shape = &bs3;
			 
			b2Body* box1 = m_world->CreateBody(bd);
			box1->CreateFixture(part_1);
			box1->CreateFixture(part_2);
			box1->CreateFixture(part_3);

			//The bar
			bd->position.Set(13,-2.5);	
			part_1->density = 30.0;	  
			b2Body* box2 = m_world->CreateBody(bd);
			box2->CreateFixture(part_1);

			// The pulley joint
			b2PulleyJointDef* myjoint = new b2PulleyJointDef();
			b2Vec2 worldAnchorOnBody1(29, 5); // Anchor point on body 1 in world axis
			b2Vec2 worldAnchorOnBody2(13, 5); // Anchor point on body 2 in world axis
			b2Vec2 worldAnchorGround1(29, 5); // Anchor point for ground 1 in world axis
			b2Vec2 worldAnchorGround2(13, 5); // Anchor point for ground 2 in world axis
			float32 ratio = 1.0f; // Define ratio
			myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
			m_world->CreateJoint(myjoint);
		}
		
		//!The sloping part in the middle -----------------------------------------------------------------------------------------------------------------
		//! This part gives direction to the ball and helps it to move to the right
		{
			b2PolygonShape plank;
			plank.SetAsBox(20.0f, 0.2f);
			b2BodyDef bd;
			bd.position.Set(10.0f, 12.5f);
			bd.angle = -0.03f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
		
		//!The supporting right rod for the balls ---------------------------------------------------------------------------------------------------------
		//! This rod holds the balls on the right, in place
		{
			b2PolygonShape plank;
			plank.SetAsBox(5.0f, 0.2f);
			b2BodyDef bd;
			bd.position.Set(34.0f, 11.0f);
			bd.angle = 0.25f * b2_pi;
			b2Body* ground = m_world->CreateBody(&bd);
			ground->CreateFixture(&plank, 0.0f);
		}
	}
	sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
