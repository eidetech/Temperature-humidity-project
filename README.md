# Temperature humidity project
Temperature and humidity measuring project for our cottage. Three sender modules and one receiver. Using nRF24L01+ modules to transfer data.

All TX's have their own id, and send data to the RX when they wake up every 7 minutes (for now). The RX will know which TX is which by it's id, and display the received data on a TFT screen.
