///Name: Momentum.h
///Purpose: declaration of functions covering  momentum of a given object in x and y directions
///Author: Piotr Satala

#pragma once

template <typename T1, typename T2, typename T3>
class Momentum
{
	T1 xVelocity;
	T2 yVelocity;
	T3 gForce;
	

public:
	
	///constructor
	Momentum(T3 g = 0, T1 Vx = 0, T2 Vy = 0) : gForce(g), xVelocity(Vx), yVelocity(Vy) {};
	

	///copy constructor
	Momentum(const Momentum& other) : xVelocity(other.xVelocity),
	                                  yVelocity(other.yVelocity),
		                              gForce(other.gForce) {};



	///destructor
	~Momentum() {};
	



	///setters
	void setXVelocity(T1 newValue) { xVelocity = newValue; }
	void setYVelocity(T2 newValue) { yVelocity = newValue; }
	void setGForce(T3 newValue) { gForce = newValue; }
	



	///getters
	T1 getXVelocity() { return xVelocity; }
	T2 getYVelocity() { return yVelocity; }
	T3 getGForce() { return gForce; }
	

	///assingment operator
	Momentum& operator=(const Momentum& other) { xVelocity = other.xVelocity;
	                                             yVelocity = other.yVelocity;
												 gForce = other.gForce;
												 return *this;
	}
};

