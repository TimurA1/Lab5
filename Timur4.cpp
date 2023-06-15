#include <iostream>
#include <string>
#include <vector>
class EventLogger {
private:
	static EventLogger* instance;
	std::vector<std::string> logEntries;
	EventLogger() {}
public:
	static EventLogger* getInstance() {
		if (instance == nullptr) {
			instance = new EventLogger();
		}
		return instance;
	}
	EventLogger(const EventLogger&) = delete;
	EventLogger& operator=(const EventLogger&) = delete;
	void logEvent(const std::string& importance, const std::string& message) {
		std::string logEntry = "[" + importance + "] " + message;
		logEntries.push_back(logEntry);
		if (logEntries.size() > 10) {
			logEntries.erase(logEntries.begin());
		}
	}
	void printLastEvents() {
		for (const auto& logEntry : logEntries) {
			std::cout << logEntry << std::endl;
		}
	}
};
EventLogger* EventLogger::instance = nullptr;
int main() {
	EventLogger* logger = EventLogger::getInstance();
	logger->logEvent("Normal", "Launch");
	logger->logEvent("Error", "Reading file error");
	logger->logEvent("Notice", "Not enough memory");
	logger->printLastEvents();
	return 0;