import React, { Component } from 'react';
import './App.css';
import $ from 'jquery';

class App extends Component {
  defaultHtml = '<i class="src">abc</i>abcdef <i class="src">abc</i> <i class="src">aa</i>';
  state = {
    html: this.defaultHtml,
    uniqueWords: [],
    wordToHighlight: ""
  }

  componentDidMount() {
    this.findUniqueWords();
  }

  render() {
    const options = this.state.uniqueWords.map(word =>
      <option key={word} value={word}>{word}</option>
    );

    return (
      <div className="App">
        <p>insert html:</p>
        <input
          defaultValue={this.defaultHtml}
          onChange={this.handleHtmlChange}></input>
        <p>select a word to <span className="highlight">highlight</span>: </p>
        <div>
          <select value={this.state.wordToHighlight} onChange={this.handleWordChange}>
            {options}
          </select>
        </div>
        <p>rendered html:</p>
        <div className="guestHtml" dangerouslySetInnerHTML={{ __html: this.state.html }}></div>
      </div>
    );
  }

  handleHtmlChange = (e) => {
    this.setState({
      html: e.target.value
    }, this.findUniqueWords);
  }

  handleWordChange = (e) => {
    try {
      let guestHtml = $(".guestHtml");

      let elements = $(`i.src`, guestHtml);
      elements.removeClass("highlight");

      elements = $(`i.src:contains(${e.target.value})`, guestHtml);
      elements.addClass("highlight");
      this.setState({
        wordToHighlight: e.target.value,
        html: guestHtml.html()
      })
    } catch (error) {
      console.log(error);
    }
  }

  findUniqueWords = () => {
    try {
      const elements = $('i.src', $(".guestHtml"));
      const uniqueWords = [...new Set(
        elements.get().map(item => { return item.innerText }))];
      this.setState(
        { uniqueWords },
        () => this.handleWordChange({
          target: {
            value: (uniqueWords.length > 0) ? uniqueWords[0] : ""
          }
        }));
    } catch (error) {
      console.log(error);
    }
  }
}

export default App;
