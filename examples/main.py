#!/usr/bin/env python3

from subprocess import Popen, PIPE
from flask import Flask
from flask import request

import os
import subprocess



program_path = "./bbcode"
project_path = "."

if not os.path.isfile(program_path):
    subprocess.call(["g++", "--std=c++11", "-o", "bbcode",
                        os.path.join(project_path, "main.cpp")])

def parse_bbcode(s):
    try:
        s = str.encode(s)
    except:
        pass
    p = Popen([program_path], stdout=PIPE, stdin=PIPE)

    result = p.communicate(input = s)[0]


    return result.decode('UTF-8')


app = Flask(__name__)

@app.route("/")
def index():
    return '''

    <!DOCUTYPE html>
    <html>
    <head>

    <script type="text/javascript">
        async function parseBBCode(event) {
            let response = await fetch('parse-bbcode/',
             {
                method: "POST",
                body: event.target.elements.bbCode.value
             });
            let data = await response.text();

            document.getElementById('result').innerHTML = data;
        }
    </script>

    </head>
    <body>
        <form onsubmit="event.preventDefault(); parseBBCode(event);" style="text-align: center;" method="post">
            <textarea name="bbCode" id="bbCode" style="width: 700px; height: 200px;"></textarea>
            <br />
            <input type="submit" />
        </form>

        <div id="result" style="border-color: black;"></div>
    </body>


    '''

@app.route("/parse-bbcode/", methods=['POST'])
def flask_parse_bbcode():
    return parse_bbcode(request.data).replace('\n', '<br />')

if __name__ == '__main__':
      app.run(host='localhost', port=6999)
