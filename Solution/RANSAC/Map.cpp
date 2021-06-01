#include <SFML/Graphics.hpp> // Include SFML graphics library

#include <iostream> // Include input and output streaming
#include <fstream> // Include input string streaming support
#include <string> // Include string support

using namespace std; // Using standard (std) namespace

int main() // Application entry point
{
    //system("echo %cd% >> fileLocation.txt");

    //std::cout << "\n\n" << system("echo %cd%") << "\n\n";

    int Magnifier = 8; // Map scale, magnify the points and render window

    auto resolution = sf::VideoMode::getDesktopMode(); // Store the devices screen resolution

    sf::RenderWindow linesRestricted(sf::VideoMode(100 * Magnifier, 100 * Magnifier), "RANSAC Line Lengths Restricted"); // Create a SFML render window instance

    linesRestricted.setPosition(sf::Vector2i((float)resolution.width / 2 - (linesRestricted.getSize().x / 10) + 50.0f,
        ((float)resolution.height / 2 - linesRestricted.getSize().y / 2) - (0.04f * (float)resolution.height))); // Cemtralise the SFML render windows position, relative to the devices screen resolution

    sf::RenderWindow linesUnrestricted(sf::VideoMode(100 * Magnifier, 100 * Magnifier), "RANSAC Line Lengths Unrestricted"); // Create a SFML render window instance

    linesUnrestricted.setPosition(sf::Vector2i((float)resolution.width / 2 - ((linesUnrestricted.getSize().x / 2) * 2) - 50.0f,
        ((float)resolution.height / 2 - linesUnrestricted.getSize().y / 2) - (0.04f * (float)resolution.height))); // Cemtralise the SFML render windows position, relative to the devices screen resolution

    int coordinateIncrementer = 0; // Number of coordinates (lines - pairs of points) stored in the array
    int pointIncrementer = 0; // Cumulative number of 'X' and 'Y' values stored in the array for the current section of coordinates 

    float coordinates[10000][4]; // All of the coordinate sections and corresponding points to draw a line

    string sX1 = ""; // 'X1' value of the currently iterated sections coordinate (string format)
    string sY1 = ""; // 'Y1' value of the currently iterated sections coordinate (string format)
    string sX2 = ""; // 'X2' value of the currently iterated sections coordinate (string format)
    string sY2 = ""; // 'Y2' value of the currently iterated sections coordinate (string format)

    float fX1 = 0.0; // 'X1' value of the currently iterated sections coordinate (integral format)
    float fY1 = 0.0; // 'Y1' value of the currently iterated sections coordinate (integral format)
    float fX2 = 0.0; // 'X2' value of the currently iterated sections coordinate (integral format)
    float fY2 = 0.0; // 'Y2' value of the currently iterated sections coordinate (integral format)

    ifstream ransacCoordinates("RansacCoordinates.csv"); // File location of RANSAC coordinates   <-------- change to "D:\MobileRobotics\Coursework\RANSAC" for example
    
    if (ransacCoordinates.is_open()) // If the RANSAC coordinates file has been opened, do the following
    {
        cout << "Opened 'RANSAC coordinates' file!" << endl; // Output the file opened to the console window
    }

    while (ransacCoordinates.good()) // While the file is streamable, do the following
    {
        if (pointIncrementer == 0) // If the point count is '0' (X1), do the following
        {
            getline(ransacCoordinates, sX1, ','); // Get the data on the current line, up until a "," has been reached (delimiter - comma)
            fX1 = (float)atof(sX1.c_str()); // Cast the streamed data to a float (casted to C style string before converted to a double)
            coordinates[coordinateIncrementer][pointIncrementer] = fX1; // Store the coordinate value at the current coordinate and point index
            cout << "X1: " << coordinates[coordinateIncrementer][pointIncrementer] << " Coordinate: " << coordinateIncrementer << endl; // Output the coordinate value at the current coordinate and point index and its belonging section to the console window
        }
        else if (pointIncrementer == 1) // If the point count is '1' (Y1), do the following
        {
            getline(ransacCoordinates, sY1, ','); // Get the data on the current line, up until a "," has been reached (delimiter - comma)
            fY1 = (float)atof(sY1.c_str()); // Cast the streamed data to a float (casted to C style string before converted to a double)
            coordinates[coordinateIncrementer][pointIncrementer] = fY1; // Store the coordinate value at the current coordinate and point index
            cout << "Y1: " << coordinates[coordinateIncrementer][pointIncrementer] << " Coordinate: " << coordinateIncrementer << endl; // Output the coordinate value at the current coordinate and point index and its belonging section to the console window
        }
        else if (pointIncrementer == 2) // If the point count is '0' (X2), do the following
        {
            getline(ransacCoordinates, sX2, ','); // Get the data on the current line, up until a "," has been reached (delimiter - comma)
            fX2 = (float)atof(sX2.c_str()); // Cast the streamed data to a float (casted to C style string before converted to a double)
            coordinates[coordinateIncrementer][pointIncrementer] = fX2; // Store the coordinate value at the current coordinate and point index
            cout << "X2: " << coordinates[coordinateIncrementer][pointIncrementer] << " Coordinate: " << coordinateIncrementer << endl; // Output the coordinate value at the current coordinate and point index and its belonging section to the console window
        }
        else if (pointIncrementer == 3) // If the point count is '0' (Y2), do the following
        {
            getline(ransacCoordinates, sY2, '\n'); // Get the data on the current line, up until a "\n" has been reached (delimiter - new line)
            fY2 = (float)atof(sY2.c_str()); // Cast the streamed data to a float (casted to C style string before converted to a double)
            coordinates[coordinateIncrementer][pointIncrementer] = fY2; // Store the coordinate value at the current coordinate and point index
            cout << "Y2: " << coordinates[coordinateIncrementer][pointIncrementer] << " Coordinate: " << coordinateIncrementer << endl; // Output the coordinate value at the current coordinate and point index and its belonging section to the console window
        }

        pointIncrementer++; // Increment the point count for the next iteration (store the proceeding 'X' or 'Y' value of a sections line)

        if (pointIncrementer == 4) // If the current point count is '4' (Y2), do the following
        {
            pointIncrementer = 0; // Reset the point count for streaming the next line of coordinates in the file

            coordinateIncrementer++; // Increment the number of coordinates stored into the array
        }
    }


    if (coordinateIncrementer % 2 != 0) // If the number of coordinates stored in the array has a remainder when divided by '2' (odd), do the following
    {
        coordinateIncrementer++; // Increment the number of coordinates stored in the array (handles errors)
    }

    cout << "Number of coordinates: " << coordinateIncrementer << endl; // Output the number of coordinates stored in the array to the console window

    sf::VertexArray LinesUnrestricted(sf::Lines, coordinateIncrementer); // Create a SFML vertex array, used to store line primitives (section lines)
    sf::VertexArray LinesRestricted(sf::Lines, coordinateIncrementer); // Create a SFML vertex array, used to store line primitives (section lines)

    for (int i = 0; i < coordinateIncrementer; i += 2) // For the number of coordinates stored in the array (sections), do the following
    {
        float pointOneX = coordinates[i][0] * Magnifier; // Store point ones 'X' value
        float pointOneY = 100 * Magnifier - coordinates[i][1] * Magnifier; // Store point ones 'Y' value
        float pointTwoX = coordinates[i][2] * Magnifier; // Store point twos 'X' value
        float pointTwoY = 100 * Magnifier - coordinates[i][3] * Magnifier; // Store point twos 'Y' value

        float distance = sqrt(pow(pointTwoX - pointOneX, 2) + pow(pointTwoY - pointOneY, 2)); // Calculate the distance between the points in the current iteration

        float targetDistance = 10.0f; // The maximum distance between points, used to determine whether lines are drawn

        if (distance <= targetDistance * Magnifier) // If the distance between the points is smaller than or equal to 'target distance' multiplied by the magnifier value, do the following
        {
            LinesUnrestricted[i].position = sf::Vector2f(coordinates[i][0] * Magnifier, 100 * Magnifier - coordinates[i][1] * Magnifier); // Set the position of the lines first point, for the currently iterated section of coordinates
            LinesUnrestricted[i + 1].position = sf::Vector2f(coordinates[i][2] * Magnifier, 100 * Magnifier - coordinates[i][3] * Magnifier); // Set the position of the lines second point, for the currently iterated section of coordinates

            LinesRestricted[i].position = sf::Vector2f(coordinates[i][0] * Magnifier, 100 * Magnifier - coordinates[i][1] * Magnifier); // Set the position of the lines first point, for the currently iterated section of coordinates
            LinesRestricted[i + 1].position = sf::Vector2f(coordinates[i][2] * Magnifier, 100 * Magnifier - coordinates[i][3] * Magnifier); // Set the position of the lines second point, for the currently iterated section of coordinates
        }
        else // Else if the distance between the points is larger than 'target distance' multiplied by the magnifier value, do the following
        {
            LinesUnrestricted[i].color = sf::Color(255.0f, 0.0f, 0.0f); // Set the line colour to 'red' (outlier)
            LinesUnrestricted[i + 1].color = sf::Color(255.0f, 0.0f, 0.0f); // Set the line colour to 'red' (outlier)

            LinesUnrestricted[i].position = sf::Vector2f(coordinates[i][0] * Magnifier, 100 * Magnifier - coordinates[i][1] * Magnifier); // Set the position of the lines first point, for the currently iterated section of coordinates
            LinesUnrestricted[i + 1].position = sf::Vector2f(coordinates[i][2] * Magnifier, 100 * Magnifier - coordinates[i][3] * Magnifier); // Set the position of the lines second point, for the currently iterated section of coordinates
        }
    }

    while (linesUnrestricted.isOpen()) // While the SFML render window instance is open, do the following
    {
        sf::Event linesUnrestrictedEvent; // Create a SFML event
        while (linesUnrestricted.pollEvent(linesUnrestrictedEvent)) // While the SFML event is polled, do the following
        {
            if (linesUnrestrictedEvent.type == sf::Event::Closed) // If the SFML event polls a window closed event, do the following
            {
                linesUnrestricted.close(); // Close the SFML render window instance
            }
        }

        sf::Event linesRestrictedEvent; // Create a SFML event
        while (linesRestricted.pollEvent(linesRestrictedEvent)) // While the SFML event is polled, do the following
        {
            if (linesRestrictedEvent.type == sf::Event::Closed) // If the SFML event polls a window closed event, do the following
            {
                linesRestricted.close(); // Close the SFML render window instance
            }
        }

        linesUnrestricted.clear(); // Clear the SFML render window
        linesUnrestricted.draw(LinesUnrestricted); // Draw the vertex array of line primitives (section lines)
        linesUnrestricted.display(); // Display the SFML render window and its contents

        linesRestricted.clear(); // Clear the SFML render window
        linesRestricted.draw(LinesRestricted); // Draw the vertex array of line primitives (section lines)
        linesRestricted.display(); // Display the SFML render window and its contents
    }

    return 0; // Return '0' (error checking)
}