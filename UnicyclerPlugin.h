#ifndef UNICYCLERPLUGIN_H
#define UNICYCLERPLUGIN_H

#include "Plugin.h"
#include "PluginProxy.h"
#include <string>
#include <vector>

class UnicyclerPlugin : public Plugin
{
public: 
 std::string toString() {return "Unicycler";}
 void input(std::string file);
 void run();
 void output(std::string file);

private: 
 std::string inputfile;
 std::string outputfile;
 std::vector<std::string> fastqFiles;
};

#endif
