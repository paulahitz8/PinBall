#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif


// Pivot 0, 0
int background[147] = {
	597, 931,
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
	532, 347,
	538, 330,
	529, 321,
	527, 304,
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
	542, 318,
	550, 350,
	554, 442,
	556, 528,
	557, 646,
	556, 755,
	554, 877,
	562, 877,
	562, 931,
	597
};

// Pivot 0, 0
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
	89, 638,
	102, 639,
	100, 703,
	99, 726,
	107, 747,
	201, 809,
	200, 823,
	188, 830,
	107, 784,
	89, 755,
	87, 675
};

int hockeyright[20] = {
	486, 639,
	487, 731,
	480, 747,
	387, 810,
	388, 825,
	405, 827,
	471, 790,
	493, 760,
	499, 726,
	498, 638
};

//rebota
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

//rebota
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

//rebota
int bumperright[16] = {
	446, 641,
	440, 633,
	433, 642,
	393, 741,
	393, 751,
	406, 750,
	412, 744,
	432, 673
};

//rebota
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

//rebota
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

//rebota
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

//overlap
int waterwall1[96] = {
	185, 467,
	101, 322,
	52, 235,
	8, 160,
	3, 115,
	12, 69,
	41, 26,
	87, -3,
	176, -3,
	226, 25,
	293, 43,
	345, 42,
	415, 35,
	477, 50,
	543, 91,
	586, 144,
	606, 192,
	613, 246,
	609, 290,
	588, 348,
	564, 396,
	540, 448,
	517, 495,
	497, 542,
	490, 560,
	487, 618,
	488, 663,
	494, 662,
	493, 604,
	495, 565,
	514, 518,
	606, 318,
	618, 262,
	617, 206,
	592, 140,
	547, 83,
	482, 42,
	419, 27,
	341, 34,
	286, 35,
	223, 16,
	179, -19,
	77, -18,
	37, 18,
	12, 52,
	-2, 86,
	2, 161,
	182, 472
};

//overlap
int waterwall2[102] = {
	153, 339,
	89, 229,
	48, 155,
	40, 124,
	45, 82,
	75, 44,
	106, 29,
	145, 28,
	192, 48,
	258, 73,
	315, 78,
	374, 71,
	430, 70,
	480, 89,
	529, 124,
	559, 170,
	574, 211,
	577, 252,
	574, 289,
	552, 340,
	488, 476,
	475, 503,
	463, 529,
	454, 561,
	451, 609,
	453, 664,
	446, 664,
	445, 580,
	457, 524,
	486, 469,
	548, 337,
	568, 287,
	570, 227,
	557, 185,
	533, 144,
	508, 115,
	476, 94,
	436, 79,
	412, 76,
	376, 77,
	317, 85,
	263, 80,
	214, 63,
	171, 44,
	136, 32,
	104, 35,
	77, 51,
	51, 82,
	46, 124,
	57, 158,
	215, 426
};

//boost and deny
int waterboost1[8] = {
	202, 421,
	171, 439,
	165, 432,
	198, 414
};

//boost and deny
int waterboost2[8] = {
	454, 641,
	489, 640,
	489, 631,
	454, 631
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


	CreateChain(0, 0, background, 147);
	CreateChain(0, 0, background2, 101);
	CreateChain(0, 0, randomcollider, 17);
	CreateChain(0, 0, rectangle1, 8);
	CreateChain(0, 0, rectangle2, 8);
	CreateChain(0, 0, hockeyleft, 22);
	CreateChain(0, 0, hockeyright, 20);
	CreateChain(0, 0, bumperclock, 26);
	CreateChain(0, 0, backbumperleft, 10);
	CreateChain(0, 0, bumperleft, 14);
	CreateChain(0, 0, backbumperright, 14);
	CreateChain(0, 0, bumperright, 16);
	CreateChain(0, 0, circle1, 24);
	CreateChain(0, 0, circle2, 24);
	CreateChain(0, 0, circle3, 20);
	CreateChain(0, 0, waterwall1, 96);
	CreateChain(0, 0, waterwall2, 104);
	CreateChain(0, 0, waterboost1, 8);
	CreateChain(0, 0, waterboost2, 8);

	return true;
}

// 
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

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
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

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
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

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	//body.type = b2_dynamicBody;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

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
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	b2Body* body_clicked = nullptr;
	b2Vec2 mouse_position;
	mouse_position.x = PIXEL_TO_METERS(App->input->GetMouseX());
	mouse_position.y = PIXEL_TO_METERS(App->input->GetMouseY());

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
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				if (f->TestPoint(mouse_position))
					body_clicked = b;
			}
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (body_clicked != nullptr)
	{
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = body_clicked;
		def.target = mouse_position;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * body_clicked->GetMass();
		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}

	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mouse_joint != nullptr)
	{
		mouse_joint->SetTarget(mouse_position);
	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && mouse_joint != nullptr)
	{
		world->DestroyJoint(mouse_joint);
		mouse_joint = nullptr;
		body_clicked = nullptr;
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