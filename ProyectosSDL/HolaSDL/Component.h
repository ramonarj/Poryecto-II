#pragma once

class Component {

private:
	bool enabled_;

public:
	void setEnabled(bool enabled) { enabled_ = enabled; };
	bool isEnabled() { return enabled_; };
	Component();
	~Component();
};

