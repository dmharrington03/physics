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


function NavHeader(props) {

    const bgStyle = {
        backgroundImage: `linear-gradient(to right, rgba(50, 50, 50, 0), rgba(20, 20, 20, .8)), 
                    url('img/img${ props.index }.png')`,
        backgroundRepeat: 'no-repeat',
        backgroundAttachment: 'fixed'
    };
    
    const out = 
    <div>
        <div uk-sticky="sel-target: .uk-navbar-container; cls-active: uk-navbar-sticky">
            <nav id="nav-bg" className="uk-navbar-container uk-light uk-fixed">
                <div className="uk-navbar-center">
                    <a href="" className="uk-navbar-item uk-logo">Computational Physics</a>
                </div>
            </nav>
        </div>
        <div id="header-bg" 
            className="uk-background-cover uk-background-top-left
            uk-height-large 
            uk-light uk-flex uk-flex-center uk-flex-middle" 
            uk-parallax="bgy: 0, -150;"
            style={ bgStyle }>
            <h1>{ props.title }</h1> 
        </div>
    </div>;
    
    return out;
}


ReactDOM.render(<NavHeader title="Kinematics - 1D" index="0"/>, document.getElementById('head'));
UIkit.navbar(document.getElementById('nav-bg'), {});
