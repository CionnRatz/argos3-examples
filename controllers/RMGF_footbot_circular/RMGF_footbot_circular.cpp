/* Include the controller definition */
#include "RMGF_footbot_circular.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>


/****************************************/
/****************************************/

CRMGFFootBotCircular::CRMGFFootBotCircular() :
   m_pcWheels(NULL),
   m_fRadius(1.0f),
   m_cCenter(0.0f,0.0f),
   m_fWheelVelocity(1.0f)
   {}

/****************************************/
/****************************************/

void CRMGFFootBotCircular::Init(TConfigurationNode& t_node) {
   /*
    * Get sensor/actuator handles
    *
    * The passed string (ex. "differential_steering") corresponds to the
    * XML tag of the device whose handle we want to have. For a list of
    * allowed values, type at the command prompt:
    *
    * $ argos3 -q actuators
    *
    * to have a list of all the possible actuators, or
    *
    * $ argos3 -q sensors
    *
    * to have a list of all the possible sensors.
    *
    * NOTE: ARGoS creates and initializes actuators and sensors
    * internally, on the basis of the lists provided the configuration
    * file at the <controllers><footbot_diffusion><actuators> and
    * <controllers><footbot_diffusion><sensors> sections. If you forgot to
    * list a device in the XML and then you request it here, an error
    * occurs.
    */
   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   /*
    * Parse the configuration file
    *
    * The user defines this part. Here, the algorithm accepts three
    * parameters and it's nice to put them in the config file so we don't
    * have to recompile if we want to try other settings.
    */
   GetNodeAttributeOrDefault(t_node, "radius", m_fRadius, m_fRadius);
   GetNodeAttributeOrDefault(t_node, "center", m_cCenter, m_cCenter);
   GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
}

/****************************************/
/****************************************/

void CRMGFFootBotCircular::ControlStep() {
   
   // Ok, now very trivially we simply set different wheel velocities
   // in order to follow a circular trajectory
   
   m_pcWheels->SetLinearVelocity(m_fWheelVelocity, 0.8*m_fWheelVelocity);
}

/****************************************/
/****************************************/

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the configuration file to refer to this
 * controller.
 * When ARGoS reads that string in the configuration file, it knows which
 * controller class to instantiate.
 * See also the configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CRMGFFootBotCircular, "RMGF_footbot_circular_controller")
