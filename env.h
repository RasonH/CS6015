//
// Created by Rason Hung on 4/9/23.
//

#pragma include once
#include <string>
#include "pointer.h"

CLASS(Val);

CLASS (Env) {
 public:
	virtual ~Env() {};
	static PTR(Env)empty;
	virtual PTR(Val)lookup(std::string find_name) = 0;

};

class EmptyEnv : public Env {
 public:
	EmptyEnv();
	PTR(Val)lookup(std::string find_name) override;
};

class ExtendedEnv : public Env {
 public:
	std::string name;
	PTR(Val)val;
	PTR(Env)rest;

	ExtendedEnv(std::string name, PTR(Val)val, PTR(Env)rest);
	PTR(Val)lookup(std::string find_name) override;
};

