#include "Vehicle.h"
#include "AgentPoursuiveur.h"
#include "2d/C2DMatrix.h"
#include "2d/Geometry.h"
#include "SteeringBehaviors.h"
#include "2d/Transformations.h"
#include "GameWorld.h"
#include "misc/CellSpacePartition.h"
#include "misc/cgdi.h"

using std::vector;
using std::list;


//----------------------------- ctor -------------------------------------
//------------------------------------------------------------------------
AgentPoursuiveur::AgentPoursuiveur(GameWorld* world,
               Vector2D position,
               double    rotation,
               Vector2D velocity,
               double    mass,
               double    max_force,
               double    max_speed,
               double    max_turn_rate,
               double    scale):    Vehicle (world,
											position,
											rotation,
											velocity,
											mass,
											max_force,
											max_speed,
											max_turn_rate,
											scale),

                                       m_pWorld(world),
                                       m_vSmoothedHeading(Vector2D(0,0)),
                                       m_bSmoothingOn(false),
                                       m_dTimeElapsed(0.0)
{  
  InitializeBuffer();

  //set up the steering behavior class
  

  //set up the smoother
  m_pHeadingSmoother = new Smoother<Vector2D>(Prm.NumSamplesForSmoothing, Vector2D(0.0, 0.0)); 
  
 
}

//---------------------------- dtor -------------------------------------
//-----------------------------------------------------------------------
AgentPoursuiveur::~AgentPoursuiveur()
{
  delete m_pHeadingSmoother;
}

//------------------------------ Update ----------------------------------
//
//  Updates the vehicle's position from a series of steering behaviors
//------------------------------------------------------------------------

void AgentPoursuiveur::fixSteerin(Vehicle* _p)
{
	this->Steering()->AgentPursuitOn(_p,Vector2D(1,1));
}

//----------------------------- InitializeBuffer -----------------------------
//
//  fills the vehicle's shape buffer with its vertices
//-----------------------------------------------------------------------------
void AgentPoursuiveur::InitializeBuffer()
{
  const int NumVehicleVerts = 3;

  Vector2D vehicle[NumVehicleVerts] = {Vector2D(-1.0f,0.6f),
                                        Vector2D(1.0f,0.0f),
                                        Vector2D(-1.0f,-0.6f)};

  //setup the vertex buffers and calculate the bounding radius
  for (int vtx=0; vtx<NumVehicleVerts; ++vtx)
  {
    m_vecVehicleVB.push_back(vehicle[vtx]);
  }
}
