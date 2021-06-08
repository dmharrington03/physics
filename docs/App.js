var converter = new showdown.Converter();
fetch("/markdown/kinematics-1d.md")
    .then((response) => response.text())
    .then((text) => document.getElementById('content').innerHTML += converter.makeHtml(text))
    .then(() => renderMathInElement(document.body, {
        // customised options
        // • auto-render specific keys, e.g.:
        delimiters: [
            {left: '$$', right: '$$', display: true},
            {left: '$', right: '$', display: false},
            {left: '\\(', right: '\\)', display: false},
            {left: '\\[', right: '\\]', display: true}
        ],
        // • rendering keys, e.g.:
        throwOnError : false
    }))
    .then(() => Prism.highlightAll())
    .catch((error) => console.log(error));


function NavHeader() {
    const out = <div uk-sticky="sel-target: .uk-navbar-container; cls-active: uk-navbar-sticky">
                    <nav id="nav-bg" className="uk-navbar-container uk-light uk-fixed">
                        <div className="uk-navbar-center">
                            <a href="" className="uk-navbar-item uk-logo">Computational Physics</a>
                        </div>
                    </nav>
                </div>;
    return out;
}


ReactDOM.render(<NavHeader />, document.getElementById('head'));
UIkit.navbar(document.getElementById('nav-bg'), {});