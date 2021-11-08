### Sensors Folder
- Put sensor interfaces here. 
- Exception is motor encoder sensors, which may end up residing in motors cpp file.

#### Guidlines for sensor APIs
- All initialization work should be done in the constructor
- If possible, calibration values should be stored ahead of time and placed in the relevant header files at `#defines`
- Class constructor should *not* interface with hardware at all
- Use `init` method to set up hardware
- Use `run` method to enable sensor operation
