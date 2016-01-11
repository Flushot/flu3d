#include "AudioEntity.h"
#include "Exceptions.h"

AudioEntity::AudioEntity() : Entity() {
		_fileName = NULL;
		_isLoop = false;
}
AudioEntity::~AudioEntity() {
}

void AudioEntity::loadFile(const char *fileName) {
	throw new NotImplementedException();
}

void AudioEntity::render() {
	throw new NotImplementedException();
}

