#include "PGObject.h"


using namespace std;
std::mt19937_64 PGObject::random = std::mt19937_64(0);

PGObject::PGObject() {
	serial = random();
	variables = unique_ptr<std::map<std::string, std::shared_ptr<PGObject>>>(new std::map<std::string, std::shared_ptr<PGObject>>());
	children = unique_ptr< std::vector<std::shared_ptr<PGObject>>>(new std::vector<std::shared_ptr<PGObject>>());
	parent = unique_ptr<PGObject>();
}
PGObject::PGObject(string name_) :PGObject(){
	simpleName = name_;
}

string PGObject::getObjectName() {
	if (parent != NULL) {
		return parent->getObjectName().append(".").append(simpleName);
	}
	else {
		return simpleName;
	}
}


unsigned long long PGObject::getSerial()
{
	return serial;
}

std::shared_ptr<PGObject> PGObject::getVariable(string name)
{
	if (variables->contains(name)) {
		return (*variables)[name];
	}
	else {
		return NULL;
	}
}

void PGObject::setVariable(std::string name, PGObject* obj)
{
	(*variables)[name] = std::shared_ptr<PGObject>(obj);
}


std::vector<shared_ptr<PGObject>>* PGObject::getChildren()
{
	return children.get();
}

PGObject *PGObject::getParent()
{
	return parent.get();
}

void PGObject::_addc(PGObject* obj) {
	children->push_back(shared_ptr<PGObject>(obj));
}
void PGObject::_addp(PGObject* obj) {
	parent.reset(obj);
}

void PGObject::addChild(PGObject* obj) {
	_addc(obj);
	obj->_addp(this);
}
void PGObject::addParent(PGObject* obj) {
	_addp(obj);
	obj->_addc(this);
}