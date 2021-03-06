#include "traci/Core.h"
#include "traci/Launcher.h"
#include "traci/LiteAPI.h"
#include "traci/API.h"
#include <inet/common/ModuleAccess.h>

Define_Module(traci::Core)

namespace
{
const simsignal_t initSignal = omnetpp::cComponent::registerSignal("traci.init");
const simsignal_t stepSignal = omnetpp::cComponent::registerSignal("traci.step");
const simsignal_t closeSignal = omnetpp::cComponent::registerSignal("traci.close");
}

namespace traci
{

Core::Core() : m_traci(new API()), m_lite(new LiteAPI(*m_traci))
{
}

int Core::numInitStages() const
{
    return 3;
}

void Core::initialize(int stage)
{
    if (stage == 0) {
        m_updateEvent = new omnetpp::cMessage("TraCI step");
        omnetpp::cModule* manager = getParentModule();
        m_launcher = inet::getModuleFromPar<Launcher>(par("launcherModule"), manager);
        m_stopping = par("selfStopping");
    } else if (stage == 1) {
        m_traci->connect(m_launcher->launch());
        checkVersion();
        emit(initSignal, simTime());
    } else if (stage == 2) {
        m_updateInterval = time_cast(m_traci->simulation.getDeltaT());
        scheduleAt(simTime() + m_updateInterval, m_updateEvent);
    }
}

void Core::finish()
{
    emit(closeSignal, simTime());
    cancelAndDelete(m_updateEvent);
    m_traci->close();
}

void Core::handleMessage(omnetpp::cMessage* msg)
{
    if (msg == m_updateEvent) {
        m_traci->simulationStep();
        emit(stepSignal, simTime());

        if (!m_stopping || m_traci->simulation.getMinExpectedNumber() > 0) {
            scheduleAt(simTime() + m_updateInterval, m_updateEvent);
        }
    }
}

void Core::checkVersion()
{
    int expected = par("version");
    if (expected == 0) {
        expected = constants::TRACI_VERSION;
        EV_INFO << "Defaulting expected TraCI API level to client API version " << expected << endl;
    }

    const auto actual = m_traci->getVersion();
    EV_INFO << "TraCI server is " << actual.second << " with API level " << actual.first << endl;

    if (expected < 0) {
        EV_DEBUG << "No specific TraCI server version requested, accepting connection..." << endl;
    } else if (expected != actual.first) {
        EV_FATAL << "Reported TraCI server version does not match expected version " << expected << endl;
        throw cRuntimeError("TraCI server version mismatch (expected: %i, actual: %i)", expected, actual.first);
    }
}

LiteAPI& Core::getLiteAPI()
{
    return *m_lite;
}

} // namespace traci
