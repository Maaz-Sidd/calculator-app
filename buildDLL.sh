#!/bin/bash

MSBuild.exe "./calculator-service/Calculator.sln" //t:Rebuild //p:Configuration=Debug //p:Platform=x64
