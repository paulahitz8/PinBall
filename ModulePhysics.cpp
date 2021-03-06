#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"
#include "ModulePlayer.h"
#include "EndScreen.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

int background[146] = {
	597, 878,
	604, 878,
	603, 765,
	603, 628,
	603, 524,
	602, 447,
	595, 372,
	588, 308,
	574, 257,
	555, 220,
	529, 184,
	499, 146,
	475, 122,
	449, 99,
	419, 80,
	390, 64,
	305, 57,
	274, 27,
	227, 2,
	159, 4,
	122, 29,
	94, 58,
	67, 97,
	47, 137,
	30, 174,
	21, 212,
	14, 259,
	11, 309,
	14, 354,
	25, 400,
	90, 544,
	84, 553,
	70, 563,
	56, 591,
	55, 877,
	91, 877,
	91, 818,
	238, 897,
	238, 996,
	352, 995,
	352, 898,
	499, 817,
	499, 879,
	536, 878,
	535, 595,
	526, 570,
	510, 554,
	480, 545,
	477, 405,
	541, 346,
	546, 331,
	541, 313,
	534, 302,
	513, 270,
	497, 239,
	477, 207,
	357, 166,
	355, 107,
	364, 102,
	381, 108,
	435, 145,
	482, 195,
	514, 244,
	546, 316,
	550, 350,
	554, 442,
	556, 528,
	557, 646,
	556, 755,
	554, 877,
	562, 877,
	562, 931,
	597, 931
};

int background2[101] = {
	205, 53,
	232, 109,
	231, 159,
	226, 166,
	137, 198,
	138, 223,
	142, 251,
	155, 295,
	177, 345,
	208, 407,
	207, 415,
	180, 373,
	158, 333,
	141, 299,
	126, 244,
	124, 201,
	114, 228,
	106, 264,
	108, 307,
	117, 346,
	149, 405,
	188, 472,
	181, 478,
	140, 408,
	115, 359,
	103, 316,
	100, 270,
	107, 233,
	120, 195,
	161, 128,
	136, 107,
	113, 125,
	93, 154,
	75, 185,
	64, 216,
	56, 251,
	53, 302,
	66, 355,
	87, 405,
	120, 456,
	146, 498,
	137, 505,
	96, 439,
	63, 371,
	49, 304,
	52, 240,
	65, 191,
	83, 150,
	114, 111,
	152, 77,
	205
};

int randomcollider[17] = {
	316, 326,
	297, 350,
	301, 357,
	387, 330,
	385, 322,
	365, 317,
	356, 331,
	332, 338,
	316
};

int rectangle1[8] = {
	264, 113,
	275, 113,
	275, 152,
	264, 152
};

int rectangle2[8] = {
	310, 114,
	321, 114,
	321, 152,
	309, 152
};

int hockeyleft[22] = {
	98, 645,
	98, 703,
	99, 726,
	107, 747,
	177, 795,
	176, 809,
	161, 812,
	131, 796,
	89, 755,
	88, 648,
	92, 634
};

int hockeyright[20] = {
	486, 639,
	487, 731,
	480, 747,
	411, 794,
	413, 804,
	424, 815,
	471, 790,
	493, 760,
	499, 726,
	498, 638
};

int bumperclock[26] = {
	154, 294,
	172, 303,
	237, 381,
	239, 390,
	250, 392,
	264, 408,
	267, 427,
	254, 444,
	232, 448,
	225, 435,
	220, 422,
	211, 402,
	164, 314
};

int backbumperleft[10] = {
	139, 646,
	139, 723,
	181, 749,
	175, 736,
	151, 717
};

int bumperleft[14] = {
	140, 641,
	145, 632,
	154, 644,
	193, 742,
	193, 752,
	184, 752,
	154, 681
};

int backbumperright[14] = {
	446, 646,
	448, 719,
	442, 730,
	405, 751,
	410, 735,
	436, 713,
	439, 658
};

int bumperright[14] = {
	442, 630,
	433, 642,
	393, 741,
	393, 751,
	406, 750,
	412, 744,
	432, 673
};

int circle1[24] = {
	323, 191,
	311, 195,
	302, 205,
	297, 220,
	300, 234,
	312, 243,
	326, 247,
	341, 243,
	352, 232,
	354, 214,
	347, 201,
	335, 193
};

int circle2[24] = {
	240, 225,
	228, 229,
	218, 240,
	216, 257,
	222, 270,
	232, 278,
	248, 280,
	263, 272,
	271, 259,
	269, 243,
	261, 232,
	251, 226
};

int circle3[20] = {
	335, 278,
	324, 285,
	316, 293,
	311, 305,
	313, 322,
	325, 334,
	363, 320,
	366, 306,
	360, 288,
	345, 281
};

int collider[8] = {
	107, 281,
	127, 273,
	130, 280,
	109, 289
};


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	debug = !debug;
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* big_ball = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	//big_ball->CreateFixture(&fixture);


	CreateChain(0, 0, background, 146, b2_staticBody, 0, true);
	CreateChain(0, 0, background2, 101, b2_staticBody, 0, true);
	CreateChain(0, 0, randomcollider, 17, b2_staticBody, 0, true);
	CreateChain(0, 0, rectangle1, 8, b2_staticBody, 0, true);
	CreateChain(0, 0, rectangle2, 8, b2_staticBody, 0, true);
	CreateChain(0, 0, hockeyleft, 22, b2_staticBody, 0, true);
	CreateChain(0, 0, hockeyright, 20, b2_staticBody, 0, true);
	CreateChain(0, 0, bumperclock, 26, b2_staticBody, 2, true);
	CreateChain(0, 0, backbumperleft, 10, b2_staticBody, 0, true);
	CreateChain(0, 0, bumperleft, 14, b2_staticBody, 2, true);
	CreateChain(0, 0, backbumperright, 14, b2_staticBody, 0, true);
	CreateChain(0, 0, bumperright, 14, b2_staticBody, 2, true);
	CreateChain(0, 0, circle1, 24, b2_staticBody, 0, true);
	CreateChain(0, 0, circle2, 24, b2_staticBody, 0, true);
	CreateChain(0, 0, circle3, 20, b2_staticBody, 0, true);
	CreateChain(0, 0, collider, 8, b2_staticBody, 0, true);

	return true;
}


update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType type, int restitution, bool active)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.active = active;


	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.restitution = restitution;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;
	

	return pbody;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if ((App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) && (App->end->isActive == false))
	{
		debug = !debug;
	}


	if(!debug)
		return UPDATE_CONTINUE;

	b2Body* ballClick = nullptr;
	b2Vec2 mousePos;
	mousePos.x = PIXEL_TO_METERS(App->input->GetMouseX());
	mousePos.y = PIXEL_TO_METERS(App->input->GetMouseY());

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && debug)
			{
				if (f->TestPoint(mousePos))
					ballClick = b;
			}
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (ballClick != nullptr)
	{
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = ballClick;
		def.target = mousePos;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * ballClick->GetMass();
		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}

	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mouse_joint != nullptr)
	{
		mouse_joint->SetTarget(mousePos);
	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && mouse_joint != nullptr)
	{
		world->DestroyJoint(mouse_joint);
		mouse_joint = nullptr;
		ballClick = nullptr;
	}
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}