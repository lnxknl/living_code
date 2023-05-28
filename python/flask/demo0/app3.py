from flask import Flask, request, render_template
from threading import Thread
from queue import Queue
import time

app = Flask(__name__)

input_queue = Queue(maxsize=5)
output_queue = Queue(maxsize=5)

def process_input():
    while True:
        if not input_queue.empty():
            data = input_queue.get()
            user_id = data['id']
            name = data['name']
            # Process the input data here
            processed_data = {'id': user_id, 'name': name.upper()}
            output_queue.put(processed_data)
        else:
            time.sleep(0.1)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        user_id = request.form['id']
        name = request.form['name']
        data = {'id': user_id, 'name': name}
        try:
            input_queue.put(data, block=False)
        except Queue.Full:
            print('Input queue is full')
    if not output_queue.empty():
        processed_data = output_queue.get()
        output_text = f"User ID: {processed_data['id']}, Name: {processed_data['name']}"
    else:
        output_text = ''
    return render_template('index.html', output_text=output_text)

if __name__ == '__main__':
    input_processor = Thread(target=process_input)
    input_processor.daemon = True
    input_processor.start()
    app.run(debug=True)
