require 'serialport'
require 'ffi'


port_str = "COM3"  
baud_rate = 9600
serial_port = SerialPort.new(port_str, baud_rate)

# FFI-modul för att skicka tangenttryckningar på Windows
module Keyboard
  extend FFI::Library
  ffi_lib 'user32'
  attach_function :keybd_event, [:uchar, :uchar, :int, :pointer], :void

  VK_TAB = 0x09
  VK_MENU = 0x12  # ALT-tangenten

  def self.send_key(key)
    keybd_event(key, 0, 0, nil)   # Tryck ner tangenten
    keybd_event(key, 0, 2, nil)   # Släpp tangenten
  end
end

def open_program(command)
  system(command)  # Kör ett systemkommando
end

puts "Lyssnar på Arduino..."

loop do
  if (command = serial_port.gets)
    command.strip!
    case command
    when "A"
      puts "Öppnar Google Chrome..."
      open_program("start chrome")  # Windows
  
    when "B"
      puts "Öppnar OBS Studio..."
      open_program("start obs")

    when "C"
      puts "Växlar fönster (ALT+TAB)..."
      Keyboard.send_key(Keyboard::VK_MENU)  # Tryck ALT
      Keyboard.send_key(Keyboard::VK_TAB)   # Tryck TAB

    else
      puts "Okänt kommando: #{command}"
    end
  end
end