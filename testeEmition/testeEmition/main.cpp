#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <mcp23017.h>
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include "CRadio.h"

// Broche LED - La broche WiringPi 0 est BCM_GPIO 17.
// nous devons utiliser la numérotation BCM au moment de l'initialisation à l'aide de wiringPiSetupSys
// si vous choisissez un autre numéro de broche, utilisez la numérotation BCM, et
// mettez à jour la commande Pages de propriétés - Événements de build - Événement postbuild distant
// qui utilise l'exportation gpio pour la configuration de wiringPiSetupSys


int main(void)
{
	char data = 'a';

	wiringPiSetup();

	CRadio maRadio("/dev/ttyUSB0", 19200);

	if (!maRadio.IsOpen()) {
		std::cerr << "Erreur lors de l'ouverture du port série." << std::endl;
		return 1;
	}
	maRadio.Send(data);
	std::cerr << "char envoier " <<data<< std::endl;

	return 0;
}