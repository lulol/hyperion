
// Utils includes
#include <utils/RgbImage.h>
#include <utils/jsonschema/JsonFactory.h>

// Hyperion includes
#include <hyperion/Hyperion.h>
#include <hyperion/ImageToLedsMap.h>

using namespace hyperion;

int main()
{
	std::string homeDir = getenv("RASPILIGHT_HOME");

	const std::string schemaFile = homeDir + "/hyperion.schema.json";
	const std::string configFile = homeDir + "/hyperion.config.json";

	Json::Value config;
	if (JsonFactory::load(schemaFile, configFile, config) < 0)
	{
		std::cerr << "UNABLE TO LOAD CONFIGURATION" << std::endl;
		return -1;
	}

	const LedString ledString = Hyperion::createLedString(config["leds"]);

	const RgbColor testColor = {64, 123, 12};

	RgbImage image(64, 64, testColor);
	ImageToLedsMap map(64, 64, ledString.leds());

	std::vector<RgbColor> ledColors(ledString.leds().size());
	map.getMeanLedColor(image, ledColors);

	std::cout << "[";
	for (const RgbColor & color : ledColors)
	{
		std::cout << color;
	}
	std::cout << "]" << std::endl;

	return 0;
}
