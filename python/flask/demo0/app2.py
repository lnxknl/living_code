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
            text = input_queue.get()
            # Process the input text here
            processed_text = text.upper()
            output_queue.put(processed_text)
        else:
            time.sleep(0.1)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        text = request.form['text']
        try:
            input_queue.put(text, block=False)
        except Queue.Full:
            print('Input queue is full')
    if not output_queue.empty():
        output_text = output_queue.get()
    else:
        output_text = ''
    return render_template('index.html', output_text=output_text)

if __name__ == '__main__':
    input_processor = Thread(target=process_input)
    input_processor.daemon = True
    input_processor.start()
    app.run(debug=True)
