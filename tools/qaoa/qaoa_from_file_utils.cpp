/*******************************************************************************
 * Copyright (c) 2020 UT-Battelle, LLC.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompanies this
 * distribution. The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html and the Eclipse Distribution
 *License is available at https://eclipse.org/org/documents/edl-v10.php
 *
 * Contributors:
 * Anthony Santana - initial API and implementation
 ******************************************************************************/

#include "qaoa_from_file.hpp"

int main(int argc, char **argv)
{
    // Default settings if user doesn't specify:
    int nbSteps = 1; 
    int maxIters = 15;
    std::string accName = "qpp";
    std::string optName = "nlopt";
    std::string optAlgo = "l-bfgs";
    std::string graphFile = "temp";
    std::string configFile = "temp";
    std::string connectFile = "temp";
    bool inConfig = false;
    bool outFile = false;
    bool verbose = true;
    float stepSize = 0.1;

    std::vector<std::string> arguments(argv + 1, argv + argc);
    for (int i = 0; i < arguments.size(); i++) {
        if (arguments[i] == "-c"){
            configFile = arguments[i+1];
            inConfig = true;
            break;
        }
        if (arguments[i] == "-i") {
           graphFile = arguments[i+1];
        }   
        if (arguments[i] == "-o") {
           outFile = (arguments[i+1] == "true");
        }   
        if (arguments[i] == "-p") {
            nbSteps = std::stoi(arguments[i+1]);
        }
        if (arguments[i] == "-qpu") {
            accName = arguments[i+1];
        }
        if (arguments[i] == "-opt") {
            optName = arguments[i+1];
        }
    }
    xacc::Initialize(argc, argv);

    // Instantiate class
    qaoa_from_file QAOA(configFile, graphFile, connectFile, outFile, optName, optAlgo, accName, inConfig, nbSteps, stepSize, maxIters, verbose);

    // Execute the QAOA algorithm and return results
    QAOA.execute();
}