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
    root.geometry("500x500")
    root.configure(bg='lightblue')
    root.resizable(False, False)
    return root


#these elements are not modified by serialLine
def configure_static_elements(root):
    title = tk.Label(root, text="Car Washing Dashboard", font=('Arial', 20), bg='lightblue', fg="green")
    title.grid(row=0, column=0)
    static_elements = [
        ("Actual Wash Number: ", 1),
        ("Info about Actual Washing", 3),
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
    global status
    global currentTemperature
    global message

    wash_counter=tk.StringVar()
    status = tk.StringVar()
    currentTemperature = tk.StringVar()
    message=tk.StringVar()
    

    wash_counter.set("counter")
    status.set("washing state")
    currentTemperature.set("20")
    message.set("message")

    dynamic_elements = [
        (tk.Label, wash_counter, 1),
        (tk.Label, status, 4),
        (tk.Label, currentTemperature, 5),
        (tk.Label, message, 6)
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
    #TODO: do the rest part after button click: input on serial line to restart arduino

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
    splitted_message=decoded_packet.split(":")
    message_type=splitted_message[0]
    message=splitted_message[1]

    if message_type=="err":
        show_button()
        pass #TODO: call function handle_error(), do the same with other elif.
    elif message_type=="sts":
        status.set(message)
    elif message_type=="cnt":
        pass #TODO
    elif message_type=="out":
        pass #TODO
    elif message_type=="":
        pass #TODO

'''
Send a packet to arduino formatted in a certain way
'''
def send_packet(packet):
    pass


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

