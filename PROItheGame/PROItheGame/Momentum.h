///Name: Momentum.h
///Purpose: declaration of functions covering  momentum of a given object in x and y directions
///Author: Piotr Satala

#pragma once

class Momentum
{
	double xVelocity;
	double yVelocity;
	double gForce;
	

public:
	///constructor
	Momentum(double g = 0, double Vx = 0, double Vy = 0) : gForce(g), xVelocity(Vx), yVelocity(Vy) {};
	
	///copy constructor
	Momentum(const Momentum& other) : xVelocity(other.xVelocity),
	                                  yVelocity(other.yVelocity),
		                              gForce(other.gForce) {};


	///destructor
	~Momentum() {};
	
	///setters
	void setXVelocity(double newValue) { xVelocity = newValue; }
	void setYVelocity(double newValue) { yVelocity = newValue; }
	void setGForce(double newValue) { gForce = newValue; }
	

	///getters
	double getXVelocity() { return xVelocity; }
	double getYVelocity() { return yVelocity; }
	double getGForce() { return gForce; }
	

	///assingment operator
	Momentum& operator=(const Momentum& other) { xVelocity = other.xVelocity;
	                                             yVelocity = other.yVelocity;
												 gForce = other.gForce;
												 return *this;
	}
};

