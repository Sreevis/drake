#pragma once

#include <vector>

#include <Eigen/Dense>

#include "drake/attic_warning.h"
#include "drake/common/drake_copyable.h"
#include "drake/systems/framework/context.h"
#include "drake/systems/framework/leaf_system.h"

namespace drake {
namespace systems {

/// A sink block that logs the most recent plant state and the accelerometer
/// reading.
class AccelerometerTestLogger : public LeafSystem<double> {
 public:
  DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(AccelerometerTestLogger);

  /// Constructs the accelerometer test logger system.
  ///
  /// @param plant_state_size The size of the plant's state.
  explicit AccelerometerTestLogger(int plant_state_size);

  void enable_log_to_console() { log_to_console_ = true; }

  Eigen::VectorXd get_plant_state(const Context<double>& context) const;
  Eigen::VectorXd get_plant_state_derivative(const Context<double>& context)
      const;
  Eigen::VectorXd get_acceleration(const Context<double>& context) const;

  const InputPort<double>& get_plant_state_input_port() const;
  const InputPort<double>& get_plant_state_derivative_input_port()
      const;
  const InputPort<double>& get_acceleration_input_port() const;

 private:
  // Logging is done in this method.
  EventStatus WriteToLog(const Context<double>& context) const;

  bool log_to_console_{false};
  int plant_state_derivative_port_index_{};
  int plant_state_port_index_{};
  int acceleration_port_index_{};
};

}  // namespace systems
}  // namespace drake
