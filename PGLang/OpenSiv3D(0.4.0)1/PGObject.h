#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <random>

class PGObject
{
private:
	std::string simpleName;
	unsigned long long serial;
	std::unique_ptr < std::map<std::string, std::shared_ptr<PGObject>>> variables;
	std::unique_ptr<std::vector<std::shared_ptr<PGObject>>> children;
	std::unique_ptr<PGObject> parent;

	

public:
	PGObject();//deprecated
	PGObject(std::string name);
	std::string getObjectName();
	unsigned long long getSerial();
	std::shared_ptr<PGObject> getVariable(std::string name);
	void setVariable(std::string name, PGObject *obj);
	std::vector<std::shared_ptr<PGObject>> *getChildren();
	PGObject *getParent();

	void addChild(PGObject* obj);
	void addParent(PGObject* obj);
	void _addc(PGObject* obj);
	void _addp(PGObject* obj);

	static std::mt19937_64 random;
};

