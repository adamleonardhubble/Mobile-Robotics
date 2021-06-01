File directories have been set up relatively, you should not have to do anything to
get the scene and other files to work together. But in the case is it not successful,
change the file directories within the "Coursework.ttt" (CoppeliaSim scene) file, in the 
'Pioneer_p3dx' script. Directories that need to be changed can be found at the top of the 
'sysCall_init()' function, these files are required for reading and writing mapping data.

Important to note, for the sake of the RANSAC calculations, the scenes simulation is
automated as soon as you start the simulation; let the simulation end by itself otherwise
the RANSAC output may not show the map entirely. Upon the simulation ending automatically
or yourself ending the simulation manually, allow time for RANSAC calculations to execute, 
this may take a while due to the iterations and overall complexity of calculations. If the 
"abort execution" label appears when the simualtion ends do not interact with it, otherwise 
the RANSAC calculations will be terminated. In the console output you are prompted of the 
calculations completion as a percentage and when the calculations are complete, this should 
appear as:

"RANSAC Calculation Completion [100.00 PERCENT] Coordinates: 'a number' Sections 'a number' Coordinates Per Section: 'a number'"
"RANSAC Calculations Complete!"

Once the simulation ends, allow a few seconds for a Micorosft Excel workbook "Map.xlsx" to open, 
a Microsoft Visual Studio solution "RANSAC.sln" (RANSAC SFML solution) as well, if 
your computer allows, a batch file will run "BuildRANSAC.bat" and attempt to rebuild the 
SFML solution to the latest RANSAC calculations and will further attempt to execute its 
correspondong '.exe' file as an application window. You will need to change the "RANSAC.sln" file
at line '44', where you should replace "RansacCoordinates.csv" for the absolute directory
of the file, if you do not do this the batch file will be ineffective. This is aimed to make the process
easier and more accessible to you, by ensuring that the offline maps are opened without iterrupting 
the writing/ executing stages at the end of the simulation.

Do not be overwhelmed, in the case you doubt the batch files functionality/ the security of your 
device or system, you can open its contents in 'Notepad' or any other text editing application 
installed, simply by right-clicking the batch file and selecting 'edit' or 'edit with'. This will 
not execute the batch file. In the case you allow the batch file to execute and SFML windows appear
to be entirely black, open the "RANSAC.sln" file and build the solution manually in Microsoft Visual
Studio; the batch file will indicate incompatabilies in a command line window, if any.

If you do not wish for the "Map.xlsx", "RANSAC.sln" and "BuildRANSAC.bat" files to execute and appear
when the simulation ends, set the "openFilesAutomatically" variable in the top of the sysCall_init() 
function, to 'false'. You can manually open these files otherwise, once and only once the simulation 
ends and when the RANSAC calculations are complete. Make sure all external files are closed before
and throughout simulation, this can invoke errors when trying to write data in 'sysCall_cleanup()'.

Throughout the simulations runtime, in the console ouput, you can observe the completion of the
simulation as a percentage, which refers to how many coordinates have been detected in comparison 
to RANSAC's target number of coordinates to be detected. This can be seen in the console output 
as the most-right text block, an example output you might see is:

"RANSAC [70.78 PCT] of [8798]"

Where '70.78 PCT' abbreviates '70.78 percent' and '8798' details the RANSAC's target number of 
coordinates to be detected and stored before the simulation ends. To speed up the process of 
detecting points, for the purpose of RANSAC calculations you can increase the simulation speed 
(click the hare button) to any speed desired and also thread the script (click the rocket button), 
doing this will not affect the results of the RANSAC calculations, invoke any unexpected errors or 
affect the robots behaviours.

There are several environments I have used to test edge following and wandering, if you would like
to do the same, you will need to set the boolean variable 'mainMap' to 'false'; you can find this
at the top of the 'sysCall_init()' also. This is necessary to prevent errors from occuring as
the map functionality uses the space of the most developed environment. 