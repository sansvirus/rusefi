#pragma once

#include "electronic_throttle.h"
#include "dc_motor.h"
#include "table_helper.h"
#include "pwm_generator_logic.h"
#include "airmass.h"
#include "injector_model.h"
#include "stepper.h"
#include "tunerstudio_io.h"
#include "idle_thread.h"
#include "test_executor.h"

#include "gmock/gmock.h"

class MockEtb : public IEtbController {
public:
	MockEtb();
	virtual ~MockEtb();

	// IEtbController mocks
	MOCK_METHOD(void, reset, (), (override));
	MOCK_METHOD(bool, isEtbMode, (), (const, override));
	MOCK_METHOD(void, update, (), (override));
	MOCK_METHOD(bool, init, (dc_function_e function, DcMotor* motor, pid_s* pidParameters, const ValueProvider3D* pedalMap), (override));
	MOCK_METHOD(void, setIdlePosition, (percent_t pos), (override));
	MOCK_METHOD(void, setWastegatePosition, (percent_t pos), (override));
	MOCK_METHOD(void, autoCalibrateTps, (bool), (override));
	MOCK_METHOD(const pid_state_s&, getPidState, (), (const, override));
	MOCK_METHOD(float, getCurrentTarget, (), (const, override));
	MOCK_METHOD(void, setLuaAdjustment, (percent_t adjustment), (override));


	// ClosedLoopController mocks
	MOCK_METHOD(expected<percent_t>, getSetpoint, (), (override));
	MOCK_METHOD(expected<percent_t>, observePlant, (), (override));
	MOCK_METHOD(expected<percent_t>, getOpenLoop, (percent_t setpoint), (override));
	MOCK_METHOD(expected<percent_t>, getClosedLoop, (percent_t setpoint, percent_t observation), (override));
	MOCK_METHOD(void, setOutput, (expected<percent_t> outputValue), (override));
};

class MockMotor : public DcMotor {
public:
	MockMotor();
	virtual ~MockMotor();

	MOCK_METHOD(bool, set, (float duty), (override));
	MOCK_METHOD(float, get, (), (const, override));
	MOCK_METHOD(void, enable, (), (override));
	MOCK_METHOD(void, disable, (const char *msg), (override));
	MOCK_METHOD(bool, isOpenDirection, (), (const, override));
};

class MockVp3d : public ValueProvider3D {
public:
	MockVp3d();
	virtual ~MockVp3d();

	MOCK_METHOD(float, getValue, (float xColumn, float yRow), (const, override));
};

class MockPwm : public IPwm {
public:
	MockPwm();
	virtual ~MockPwm();

	MOCK_METHOD(void, setSimplePwmDutyCycle, (float dutyCycle), (override));
};

class MockOutputPin : public OutputPin {
public:
	MockOutputPin();
	virtual ~MockOutputPin();

	MOCK_METHOD(void, setValue, (int value, bool isForce), (override));
};

class MockExecutor : public TestExecutor {
public:
	MockExecutor();
	virtual ~MockExecutor();

	MOCK_METHOD(void, schedule, (const char *msg, scheduling_s *scheduling, efitick_t timeNt, action_s const& action), (override));
	MOCK_METHOD(void, cancel, (scheduling_s*), (override));
};

class MockAirmass : public AirmassVeModelBase {
public:
	MockAirmass();
	virtual ~MockAirmass();

	MockVp3d veTable;

	MOCK_METHOD(AirmassResult, getAirmass, (float rpm, bool postState), (override));
};

class MockInjectorModel2 : public IInjectorModel {
public:
	MockInjectorModel2();
	virtual ~MockInjectorModel2();

	MOCK_METHOD(void, prepare, (), (override));
	MOCK_METHOD(floatms_t, getInjectionDuration, (float fuelMassGram), (const, override));
	MOCK_METHOD(float, getFuelMassForDuration, (floatms_t duration), (const, override));
	MOCK_METHOD(floatms_t, getDeadtime, (), (const, override));
};

class MockStepperHardware : public StepperHw {
public:
	MockStepperHardware();
	virtual ~MockStepperHardware();

	MOCK_METHOD(bool, step, (bool positive), (override));
};

class MockTsChannel : public TsChannelBase {
public:
	MockTsChannel();
	virtual ~MockTsChannel();

	MOCK_METHOD(void, write, (const uint8_t* buffer, size_t size, bool isEndOfPacket), (override));
	MOCK_METHOD(size_t, readTimeout, (uint8_t* buffer, size_t size, int timeout), (override));
};

class MockIdleController : public IdleController {
public:
	MockIdleController();
	virtual ~MockIdleController();

  MOCK_METHOD(IdleController::Phase, determinePhase, (float rpm, IdleController::TargetInfo targetRpm, SensorResult tps, float vss, float crankingTaperFraction), (override));
 	MOCK_METHOD(IdleController::TargetInfo, getTargetRpm, (float clt), (override));
	MOCK_METHOD(float, getCrankingOpenLoop, (float clt), (const, override));
	MOCK_METHOD(float, getRunningOpenLoop, (IdleController::Phase phase, float rpm, float clt, SensorResult tps), (override));
	MOCK_METHOD(float, getOpenLoop, (IdleController::Phase phase, float rpm, float clt, SensorResult tps, float crankingTaperFraction), (override));
	MOCK_METHOD(float, getClosedLoop, (IdleController::Phase phase, float tps, float rpm, float target), (override));
	MOCK_METHOD(float, getCrankingTaperFraction, (float clt), (const, override));
	MOCK_METHOD(bool, isIdlingOrTaper, (), (const, override));
	MOCK_METHOD(bool, isCoastingAdvance, (), (const, override));
	MOCK_METHOD(IdleController::Phase, getCurrentPhase, (), (const));
	MOCK_METHOD(float, getIdleTimingAdjustment, (float rpm), (override));
};

class MockIgnitionController : public IgnitionController {
public:
	MockIgnitionController();
	virtual ~MockIgnitionController();

	MOCK_METHOD(bool, getIgnState, (), (const, override));
};

class MockHpfpController : public HpfpController {
public:
	MockHpfpController();
	virtual ~MockHpfpController();

	bool isHpfpActive;
	angle_t m_deadangle;
};

class MockLimpManager : public LimpManager {
public:
	MockLimpManager();
	virtual ~MockLimpManager();
};
