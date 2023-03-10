#pragma once

#include <SDL2/SDL.h>

/** Logger namespace.
 * Usage:
 * @code
 * ...
 *     Logger::Error("Shader compilation failed: %s", infoLog);
 *     Logger::Warn("Shader compilation failed: %s", infoLog);
 *     Logger::Info("Shader compilation failed: %s", infoLog);
 * ...
 * @endcode
 */
namespace Engine::Logger {

enum class Level {
  Error = SDL_LOG_PRIORITY_ERROR,
  Warn = SDL_LOG_PRIORITY_WARN,
  Info = SDL_LOG_PRIORITY_INFO,
};

/** Log a formatted message.
 * @param level The level of the message.
 * @param format The format of the message.
 * @param ... The arguments to the format.
 */
inline void Log(Level level, const char* format, ...) {
  va_list args;
  va_start(args, format);
  SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
                  static_cast<SDL_LogPriority>(level), format, args);
  va_end(args);
}

/** Log an error message.
 * @param format The format of the message.
 * @param args The arguments to the format.
 */
template <typename... Args>
void Error(const char* format, Args... args) {
  Log(Level::Error, format, args...);
}

/** Log a warning message.
 * @param format The format of the message.
 * @param args The arguments to the format.
 */
template <typename... Args>
void Warn(const char* format, Args... args) {
  Log(Level::Warn, format, args...);
}

/** Log an info message.
 * @param format The format of the message.
 * @param args The arguments to the format.
 */
template <typename... Args>
void Info(const char* format, Args... args) {
  Log(Level::Info, format, args...);
}

}  // namespace Logger

