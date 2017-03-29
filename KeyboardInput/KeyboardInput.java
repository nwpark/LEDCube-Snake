import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JSeparator;
import javax.swing.UIManager;

import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;

import gnu.io.CommPortIdentifier;
import gnu.io.CommPort;
import gnu.io.SerialPort;
import gnu.io.PortInUseException;
import gnu.io.UnsupportedCommOperationException;

import java.io.OutputStream;
import java.io.IOException;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class KeyboardInput extends JFrame
                           implements KeyListener, ActionListener
{
  private final JButton startJButton = new JButton("Start");
  private final JButton stopJButton = new JButton("Stop");
  private final JButton refreshJButton = new JButton("Refresh");
  private JComboBox comPortJComboBox = null;

  private OutputStream out = null;
  private SerialPort serialPort = null;

  private final HashMap<String, CommPortIdentifier>
    comPorts = new HashMap<String, CommPortIdentifier>();

  private static final HashSet<Integer> acceptedKeys = new HashSet<Integer>();

  private boolean transmitting = false;

  public KeyboardInput()
  {
    try {
      UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
    } catch(Exception e) { System.out.println(e); }

    setTitle("Snake");

    Container contents = getContentPane();
    contents.setLayout(new BorderLayout());

    refreshCommPorts();
    comPortJComboBox = new JComboBox(getPortNames());
    contents.add(comPortJComboBox, BorderLayout.NORTH);
    comPortJComboBox.addKeyListener(this);

    contents.add(new JSeparator(), BorderLayout.CENTER);

    JPanel buttonsJPanel = new JPanel();
    buttonsJPanel.setLayout(new GridLayout(0, 2));
    startJButton.addActionListener(this);
    startJButton.addKeyListener(this);
    stopJButton.addActionListener(this);
    stopJButton.addKeyListener(this);
    buttonsJPanel.add(startJButton);
    buttonsJPanel.add(stopJButton);
    contents.add(buttonsJPanel, BorderLayout.SOUTH);

    addKeyListener(this);

    setDefaultCloseOperation(EXIT_ON_CLOSE);
    pack();
  } // KeyboardInput

  public void keyPressed(KeyEvent event)
  {
    int keyCode = event.getKeyCode();
    System.out.println(event.getKeyChar() + " - " + keyCode);

    try {
      if(transmitting && acceptedKeys.contains(keyCode))
        out.write(keyCode);
    } catch(IOException e) { System.err.println(e); }
  } // keyPressed

  public void keyTyped(KeyEvent event) { /*do nothing*/ }
  public void keyReleased(KeyEvent event) { /*do nothing*/ }

  public void actionPerformed(ActionEvent event)
  {
    if(event.getSource() == refreshJButton)
      refreshCommPorts();
    else if(event.getSource() == startJButton)
    {
      try {
        String comPortName = (String)comPortJComboBox.getSelectedItem();

        // open(java.lang.String theOwner, int timeout), using 2 sec timeout
        CommPort commPort
          = comPorts.get(comPortName).open("Image Uploader", 2000);
        serialPort = (SerialPort)commPort;

        // 9600 baud rate
        serialPort.setSerialPortParams(250000, SerialPort.DATABITS_8,
                                       SerialPort.STOPBITS_1,
                                       SerialPort.PARITY_NONE);

        out = serialPort.getOutputStream();
        out.flush();

        transmitting = true;
        stopJButton.setEnabled(true);
        startJButton.setEnabled(false);
      } catch(PortInUseException e) {
        System.out.println("Port in use");
      } catch(IOException e) {
        System.err.println(e);
      } catch(UnsupportedCommOperationException e) {
        System.err.println(e);
      }// catch
    } // else if
    else if(event.getSource() == stopJButton)
    {
      if(serialPort != null)
        serialPort.close();

      transmitting = false;

      startJButton.setEnabled(true);
      stopJButton.setEnabled(false);
    } // else if
  } // actionPerformed

  public String[] getPortNames()
  {
    Set<String> portNames = comPorts.keySet();
    return portNames.toArray(new String[portNames.size()]);
  } // getPortNames

  private void refreshCommPorts()
  {
    comPorts.clear();

    Enumeration<CommPortIdentifier> comPortsEnum
      = CommPortIdentifier.getPortIdentifiers();
    while(comPortsEnum.hasMoreElements())
    {
      CommPortIdentifier serialPortId = comPortsEnum.nextElement();
      comPorts.put(serialPortId.getName(), serialPortId);
    } // while
  } // refreshCommPorts

  public static void main(String[] args)
  {
    acceptedKeys.add(80); // P
    acceptedKeys.add(87); // W
    acceptedKeys.add(83); // S
    acceptedKeys.add(65); // A
    acceptedKeys.add(68); // D
    acceptedKeys.add(33); // PgUp
    acceptedKeys.add(34); // PgDn

    new KeyboardInput().setVisible(true);
  } // main

} // class KeyboardInput
