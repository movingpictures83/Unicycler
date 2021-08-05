#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "UnicyclerPlugin.h"

void UnicyclerPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string filename;
   ifile >> filename;
   if (filename.size() > 0)
   fastqFiles.push_back(filename);
 }
}

void UnicyclerPlugin::run() {
   
}

void UnicyclerPlugin::output(std::string file) {
 // spades.py -o 02_Unicycler -1 $1 -2 $2 --careful
 // unicycler -l $1 -o 03_unicycler
 // unicycler -1 $1 -2 $2 -l $3 -o hyb_unicycler
 //
	std::string command;
 if (fastqFiles.size() == 1) { // Long
   command = "unicycler -o "+file+" -l "+std::string(PluginManager::prefix())+"/"+fastqFiles[0];
 }
 else if (fastqFiles.size() == 2) { // Short, forward and reverse
   command = "unicycler -o "+file+" -1 "+std::string(PluginManager::prefix())+"/"+fastqFiles[0]+" -2 "+std::string(PluginManager::prefix())+"/"+fastqFiles[1];
 }
 else { // Hybrid, short and long
   command = "unicycler -o "+file+" -1 "+std::string(PluginManager::prefix())+"/"+fastqFiles[0]+" -2 "+std::string(PluginManager::prefix())+"/"+fastqFiles[1]+" -l "+std::string(PluginManager::prefix())+"/"+fastqFiles[2];
 }
 std::cout << command << std::endl;

 system(command.c_str());

std::string copyCommand = "cp "+file+"/assembly.fasta "+std::string(PluginManager::prefix());
 std::cout << copyCommand << std::endl;
 system(copyCommand.c_str());
}

PluginProxy<UnicyclerPlugin> UnicyclerPluginProxy = PluginProxy<UnicyclerPlugin>("Unicycler", PluginManager::getInstance());
