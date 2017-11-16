from flask import *
app = Flask(__name__)

@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@app.route('/')
def home():
    return render_template('home.html')


if __name__ == '__main__':
    app.debug = False
    app.run(host='0.0.0.0', port=5000)
