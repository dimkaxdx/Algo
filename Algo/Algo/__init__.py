from flask import *
from os import listdir
from os.path import isfile, join

app = Flask(__name__)

@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/algo', defaults={'path': ''})
@app.route('/algo/<path:path>')
def algo(path):
    if path != '':
        if '.html' not in path:
            path += '.html'
        return render_template(path)

    return render_template('algo.html')

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0', port=5000)
