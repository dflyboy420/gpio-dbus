#include <algorithm>
#include <array>
#include <chrono>
#include <cppgpio.hpp>
#include <dbus/dbus.h>
#include <functional>
#include <vector>
#include <iostream>

using namespace GPIO;
using namespace std;

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  DBusError dbus_error;
  DBusConnection *dbus_conn = nullptr;
  DBusMessage *dbus_msg = nullptr;
  DBusMessage *dbus_reply = nullptr;
  const char *dbus_result = nullptr;

  DigitalIn button(15);

  // Initialize D-Bus error
  ::dbus_error_init(&dbus_error);

  // Connect to D-Bus
  if (nullptr == (dbus_conn = ::dbus_bus_get(DBUS_BUS_SYSTEM, &dbus_error)))
  {
    ::perror(dbus_error.name);
    ::perror(dbus_error.message);

    // Compose remote procedure call
  }
  else
  {
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    std::chrono::milliseconds running;
    while (button.get_state() < 1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    if (nullptr ==
        (dbus_msg = ::dbus_message_new_method_call(
             "org.freedesktop.DBus", "/",
             "org.freedesktop.DBus.Introspectable", "Introspect")))
    {
      ::dbus_connection_unref(dbus_conn);
      ::perror("ERROR: ::dbus_message_new_method_call - Unable to allocate "
               "memory for the message!");
    }

    std::cout << "Connected to D-Bus as \""
              << ::dbus_bus_get_unique_name(dbus_conn) << "\"." << std::endl;
    std::cout << "Introspection Result:" << std::endl;
    std::cout << std::endl
              << dbus_result << std::endl
              << std::endl;
    ::dbus_message_unref(dbus_msg);
    ::dbus_message_unref(dbus_reply);

    /*
     * Applications must not close shared connections -
     * see dbus_connection_close() docs. This is a bug in the application.
     */
    //::dbus_connection_close(dbus_conn);

    // When using the System Bus, unreference
    // the connection instead of closing it
    ::dbus_connection_unref(dbus_conn);
  }

  return 0;
}