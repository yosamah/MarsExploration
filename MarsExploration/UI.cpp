#include "UI.h"

UI::UI(MarsStation* Mars)
{
	pMars = Mars;
}

void UI::Read(ifstream& file)  //file.close() //file.eof()
{
	/*The type of each rover*/
	int NumOfPolarRover;
	int NumOfMountRover;
	int NumOfEmergRover;

	/*The speed of each rover*/
	int SpeedOfPolarRover;
	int SpeedOfMountRover;
	int SpeedOfEmergRover;

	/*The number of missions needed before check up*/
	int BeforeCheckup; 

	/*The Check up duration of each rover*/
	int CheckUpDurationPolar;
	int CheckUpDurationMount;
	int CheckUpDurationEmerg;

	/* TODO: For bonus the different speeds add char "B" and check on in to read differently */
	file >> NumOfMountRover >> NumOfPolarRover >> NumOfEmergRover;
	file >> SpeedOfMountRover >> SpeedOfPolarRover >> SpeedOfEmergRover;
	file >> BeforeCheckup;
	file >> CheckUpDurationMount >> CheckUpDurationPolar >> CheckUpDurationEmerg;
	pMars->SetAvailableRovers(NumOfMountRover, NumOfPolarRover, NumOfEmergRover, SpeedOfMountRover, SpeedOfPolarRover, SpeedOfEmergRover, CheckUpDurationMount, CheckUpDurationPolar, CheckUpDurationEmerg);
	
	///////////////////       /////////////////////////
	
	int AutoPromotion;

	int NumOfEvents;

	file >> AutoPromotion;
	file >> NumOfEvents;
	
	char EventType;


	for (int i = 0; i < NumOfEvents; i++)
	{
		file >> EventType;

		if (EventType == 'F')
		{
			char MissionType;
			int ED, ID, Location, MDUR, Signif;

			file >> MissionType;
			file >> ED >> ID >> Location >> MDUR >> Signif;

			Formulation* F = new Formulation(MissionType,Location,MDUR,Signif,ID,ED);
		}
		else if (EventType == 'X')
		{
			int ED,ID;
			file >> ED >> ID;

		}

	}
}