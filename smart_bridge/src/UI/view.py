import serial
import tkinter as tk

'''
Monitoring Serial Line when a certain message is received from Serial line. The message format sent by Arduino must be:

 <message_type>:<message> 


message_type:  err=error, out=output, tmp=temperature, sts=status, cnt=counter
    -"err:message"
    -"out:message"
    -"tmp:message"
    -"sts:message"
    -"cnt:message"
'''

def create_main_window():
    root = tk.Tk()
    root.title("Car Washing Dashboard")
    root.geometry("600x600")
    root.configure(bg='lightblue')
    root.resizable(True, True)
    return root


#these elements are not modified by serialLine
def configure_static_elements(root):
    title = tk.Label(root, text="Car Washing Dashboard", font=('Arial', 20), bg='lightblue', fg="green")
    title.grid(row=0, column=0)
    static_elements = [
        ("Current Washes Number: ", 1),
        ("Info about Current Washing", 3),
        ("Current Status: ", 4),
        ("Current Temperature: ", 5),
        ("Message: ", 6)
    ]
    for text, row in static_elements:
        label = tk.Label(root, text=text, font=('Arial', 14), bg='lightblue')
        label.grid(row=row, column=0, pady=20,padx=5, sticky="w")

#these elements are modified by serialLine
def configure_dynamic_elements(root):
    global wash_counter
    global progress_status #status of the washing (washing, checkin, checkout etc...)
    global current_temperature
    global ui_message

    wash_counter=tk.StringVar()
    progress_status = tk.StringVar()
    current_temperature = tk.StringVar()
    ui_message=tk.StringVar()
    

    wash_counter.set("counter")
    progress_status.set("washing state")
    current_temperature.set("20")
    ui_message.set("message")

    dynamic_elements = [
        (tk.Label, wash_counter, 1),
        (tk.Label, progress_status, 4),
        (tk.Label, current_temperature, 5),
        (tk.Label, ui_message, 6)
    ]

    for element_type, text_var, row in dynamic_elements:
        element = element_type(root, textvariable=text_var, font=('Arial', 14), bg='lightblue')
        element.grid(row=row, column=1, sticky="w")


def configure_button(root):
    global button
    button = tk.Button(root, text="Maintenance Done!", font=('Arial', 14), bg='lightblue', fg='red', command=maintenance_done_click)
    return button


def hide_button():
    button.grid_remove()

def show_button(): #show button when an error occured
    button.grid(row=7, column=1, pady=10, columnspan=2, sticky="n")

def maintenance_done_click():
    hide_button()
    packet_to_send="mnt:done" #mnt stands for maintenance
    send_packet(packet_to_send)

def build_interface():
    global button
    root = create_main_window()
    configure_static_elements(root)
    configure_dynamic_elements(root)
    button = configure_button(root)
    return root

######################################LOGIC-MODEL

'''
This function handle the message received in this format  <message_type>:<message>.
When the packet is received it is splitted in message_type and message
then it is encapsulated into variable and shown inside UI
'''
def check_packet(decoded_packet):
    print(decoded_packet)

    if ":" in decoded_packet:
        splitted_message=decoded_packet.split(":")
        message_type=splitted_message[0]
        message=splitted_message[1]

        if message_type=="err":
            show_button()
            ui_message.set("Errore nella macchina")
        elif message_type=="sts": #washing state
            progress_status.set(message)
        elif message_type=="cnt": #wash_counter
            wash_counter.set(message)
        elif message_type=="out":
            ui_message.set(message)
        elif message_type=="tmp":
            current_temperature.set(message)
        


'''
Send a packet to arduino formatted in a certain way
'''
def send_packet(packet):
    try:
        serialInst.write(packet.encode('utf-8'))
        print(f"GUI: Pacchetto inviato con successo: {packet}")
    except Exception as e:
        print(f"Errore durante l'invio del pacchetto: {e}")


def update_serial():
    if serialInst.in_waiting:
        packet = serialInst.readline()
        decoded_packet = packet.decode('utf').rstrip('\n')
        check_packet(decoded_packet)
    root.after(100, update_serial)

def start_serial():
    global serialInst
    serialInst = serial.Serial()
    serialInst.baudrate = 9600
    serialInst.port = 'COM3' #COM3 depends on the port where Arduino is connected
    serialInst.open()
    root.after(100, update_serial)

    
################################################################################

if __name__ == '__main__':
    root = build_interface()
    root.after(10, start_serial)
    root.mainloop()

