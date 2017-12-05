#include "state.hpp"
#include "stateManager.hpp"

#include "core/engine.hpp"

void State::setManager(StateManager * manager) {
	managerRef = manager;
}

void State::setRenderer(SDL_Renderer * renderer) {
	this->renderer = renderer;
}

void State::init() {
	// do nothing lol
}

void State::setDelta(int inpDelta) {
	delta = inpDelta;
}

void State::changeState(std::unique_ptr<State> state) {
	managerRef->changeState(std::move(state));
}

void State::addState(std::unique_ptr<State> state) {
	managerRef->pushState(std::move(state));
}

void State::quitTopState() {
	managerRef->popState();
}

void State::showCursor(bool show) const {
	SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}

bool State::keyPressed(SDL_Scancode key) const {
	return managerRef->keyPressed(key);
}

int State::getMouseX() const {
	return managerRef->mouseX;
}

int State::getMouseY() const {
	return managerRef->mouseY;
}

void State::exit() {
	managerRef->quit();
}

void State::updateGameObject(GameObject & obj) {
	obj.update(delta);
}

void State::renderGameObject(GameObject & obj) const {
	obj.render(0, 0);
}

void State::renderGameObject(GameObject & obj, int camX, int camY) const {
	obj.render(camX, camY);
}

WAV_track State::loadWAV(const std::string & path, bool loop) const {
	return QcE::get_instance()->getAudioEngine()->loadWAV(path, loop);
}

WAV_track State::loadAndPlayWAV(const std::string & path, bool loop) const {
	WAV_track track = loadWAV(path, loop);
	playWAV(track);
	return track;
}

void State::playWAV(WAV_track track) const {
	QcE::get_instance()->getAudioEngine()->play(track);
}

void State::pauseWAV(WAV_track track) const {
	QcE::get_instance()->getAudioEngine()->pause(track);
}

void State::stopWAV(WAV_track track) const {
	QcE::get_instance()->getAudioEngine()->stop(track);
}

void State::createFont(const std::string & name, const std::string & path, int size) const {
	QcE::get_instance()->getTextEngine()->createFont(name, path, size);
}

SDL_Texture * State::getTextTexture(const std::string & text, const std::string font, SDL_Color colour) const {
	return QcE::get_instance()->getTextEngine()->getTexture(text, font, colour);
}