
class ITrajectoryController {
public:
	virtual ~ITrajectoryController(){

	}
	virtual void onMoveUp(float elapsedMs) = 0;
	virtual void onMoveDown(float elapsedMs) = 0;
protected:
	virtual float angleSpeedUnit() { return 0.0f; };
};