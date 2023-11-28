#include "mobile.h"
#include "game.h"
//#include "uiDraw.cpp"

#define GRAVITY -9.8067

Position Mobile::getPosition()
{
	return position;
}

double Mobile::getRadius()
{
	return radius * position.getZoom();
}

double Mobile::getHeight()
{
	return Trig::distanceBetweenPoints(Game::getEarthPosition(), position) - Game::getEarthRadius();
}

double Mobile::get_gH()
{
	return GRAVITY * pow(Game::getEarthRadius() / (Game::getEarthRadius() + getHeight()), 2);
}

double Mobile::getGravityDdx()
{
	return Trig::computeSineComponent(Trig::getAngle(position.getMetersX(), position.getMetersY()), get_gH());
}

double Mobile::getGravityDdy()
{
	return Trig::computeCosineComponent(Trig::getAngle(position.getMetersX(), position.getMetersY()), get_gH());
}

bool Mobile::isAlive()
{
	return alive;
}

void Mobile::kill()
{
	alive = false;
}

void Mobile::move()
{
	double t = Game::getTimeInterval();
	double ddx = getGravityDdx();
	double ddy = getGravityDdy();

	dx += ddx * t;
	dy += ddy * t;
	position.addMetersX(dx * t);
	position.addMetersY(dy * t);
	rotationAngle.addRadians(rotationSpeed);
}

Ship::Ship(Position pt, double dx, double dy) : Mobile()
{
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 10.0;
	rotationAngle = Angle(135.0);
	thrustAcceleration = 2.0;
	thrusterLeft = false;
	thrusterRight = false;
	thrusterMain = false;
	rotationSpeed = 0.1;
}

void Ship::move()
{
	double t = Game::getTimeInterval();
	double ddx = getGravityDdx();
	double ddy = getGravityDdy();

	if (thrusterMain) {
		ddx += Trig::computeSineComponent(rotationAngle.getRadians(), thrustAcceleration);
		ddy += Trig::computeCosineComponent(rotationAngle.getRadians(), thrustAcceleration);
	}

	dx += ddx * t;
	dy += ddy * t;
	position.addMetersX(dx * t);
	position.addMetersY(dy * t);

	if (thrusterLeft) {
		rotationAngle.addRadians(-rotationSpeed);
	}

	if (thrusterRight) {
		rotationAngle.addRadians(rotationSpeed);
	}
}

void Ship::setThrusterLeft(bool status)
{
	thrusterLeft = status;
}

void Ship::setThrusterRight(bool status)
{
	thrusterRight = status;
}

void Ship::setThrusterMain(bool status)
{
	thrusterMain = status;
}

void Ship::fire()
{
	double bulletDx = dx + Trig::computeSineComponent(rotationAngle.getRadians(), 9000);
	double bulletDy = dy + Trig::computeCosineComponent(rotationAngle.getRadians(), 9000);
	Position ptBullet = rotate(position, 0.0, 19.0, rotationAngle.getRadians());

	Game::addMobile(new Bullet(ptBullet, bulletDx, bulletDy));
}

void Ship::kill() {
	alive = false;
	Game::killShip();
}

void Ship::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawShip(position, rotationAngle.getRadians(), thrusterMain);
}

void Timed::move()
{
	Mobile::move();
	countDown();
}

void Timed::countDown()
{
	if (duration > -1) {
		duration -= 1;
	}

	if (duration == 0) {
		activate();
	}
}

void Timed::activate()
{
	kill();
}

Bullet::Bullet(Position pt, double dx, double dy) {
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 1.0;
	rotationAngle = Angle();
	rotationSpeed = 0.0;
	duration = 70;
}

void Bullet::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawProjectile(position);
}

void spawnFragment(Position pt, Angle a, Velocity v)
{
	Position ptSpawn = getSpawnPosition(pt, a);
	Velocity vSpawn = getSpawnVelocity(v, a);
	Game::addDebris(new Fragment(ptSpawn, vSpawn.getDx(), vSpawn.getDy()));
}

Position getSpawnPosition(Position pt, Angle a)
{
	return rotate(pt, 0.0, 12.0, a.getRadians());
}

Velocity getSpawnVelocity(Velocity parentV, Angle a)
{
	Velocity v = Velocity(a, random(2500.0, 4500.0));
	v.add(parentV);
	return v;
}

Fragment::Fragment(Position pt, double dx, double dy) : Timed()
{
	position = pt;
	this->dx = dx;
	this->dy = dy;
	duration = random(50, 100);
	radius = 2.0;
	rotationSpeed = 0.3;
	rotationAngle.addDegrees(random(0.0, 360.0));
}

void Fragment::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawFragment(position, rotationAngle.getRadians());
}
