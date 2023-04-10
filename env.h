//
// Created by Rason Hung on 4/9/23.
//

#ifndef MSDSCRIPT__ENV_H_
#define MSDSCRIPT__ENV_H_

#include <string>
#include "pointer.h"

CLASS(Val);

CLASS (Env) {
 public:
	static PTR(Env)empty;
	virtual PTR(Val)lookup(std::string find_name) = 0;
	~Env() = default;
};

class EmptyEnv : public Env {
 public:
	EmptyEnv();
	PTR(Val)lookup(std::string find_name);
};

class ExtendedEnv : public Env {
 public:
	std::string name;
	PTR(Val)val;
	PTR(Env)rest;

	ExtendedEnv(std::string name, PTR(Val)val, PTR(Env)rest);
	PTR(Val)lookup(std::string find_name);
};

#endif //MSDSCRIPT__ENV_H_

