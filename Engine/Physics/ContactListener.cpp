#include "ContactListener.h"
#include "../FrameWork/Actor.h"
#include "../Components/CollisionComponent.h"


namespace squampernaut
{
	void Contactlistener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			if (!actorA->IsDestroyed() && actorA->GetComponent<CollisionComponent>())
			{
				actorA->GetComponent<CollisionComponent>()->OnCollisionEnter(actorB);
			}

			if(!actorB->IsDestroyed() && actorA->GetComponent<CollisionComponent>())
			{
				actorB->GetComponent<CollisionComponent>()->OnCollisionEnter(actorA);
			}

		}
	}

	void Contactlistener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);


			if (!actorA->IsDestroyed() && actorA->GetComponent<CollisionComponent>())
			{
				actorA->GetComponent<CollisionComponent>()->OnCollisionEnter(actorB);
			}

			if (!actorB->IsDestroyed() && actorA->GetComponent<CollisionComponent>())
			{
				actorB->GetComponent<CollisionComponent>()->OnCollisionEnter(actorA);
			}

		}
	}
}
